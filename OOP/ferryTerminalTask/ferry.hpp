#pragma once
#include "list.hpp"
#include "miniBus.hpp"
#include "vehicle.hpp"

enum class FerryState { OPEN, CLOSED };

template <VehicleType TYPE, int CAPACITY, int INTERVAL> class Ferry {
private:
  List<Vehicle *> queue;
  FerryState state;
  int totalVehicles;
  int totalSeatsUsed;
  int totalMinutes;

public:
  Ferry() : state(), totalVehicles(0), totalSeatsUsed(0), totalMinutes(0) {}

  void open() {
    state = FerryState::OPEN;
    totalVehicles = 0;
    totalSeatsUsed = 0;
    totalMinutes = 0;
  }

  void close() {
    state = FerryState::CLOSED;
    queue.clear();
  }

  bool addVehicle(Vehicle *v) {
    if (v->getVehicleType() != TYPE) {
      return false;
    }

    for (int i = 1; i <= queue.size(); i++) {
      Vehicle *existing;

      queue.read(i, existing);
      if (existing->getId() == v->getId()) {
        return false;
      }
    }

    MiniBus *mb = dynamic_cast<MiniBus *>(v);

    if (mb != nullptr) {
      bool leaderFound = false;

      for (int i = 1; i <= queue.size(); i++) {
        Vehicle *potentialLeader;

        queue.read(i, potentialLeader);
        if (potentialLeader->getId() == mb->getGroupLeaderId()) {
          leaderFound = true;
          break;
        }
      }

      if (!leaderFound) {
        return false;
      }
    } else {
      if (v->getSeatsRequired() > CAPACITY) {
        return false;
      }
    }

    queue.add(queue.size() + 1, v);
    return true;
  }

  int queueSize() const { return queue.size(); }

  bool depart() {
    if (state == FerryState::CLOSED || queue.empty()) {
      return false;
    }

    int seatsThisRound{};
    int boardedVehicles{};

    for (int i = 1; i <= queue.size(); i++) {
      Vehicle *v;
      queue.read(1, v); // always peek front of queue

      if (seatsThisRound + v->getSeatsRequired() <= CAPACITY) {
        seatsThisRound += v->getSeatsRequired();
        queue.remove(1); // actually board vehicle
        boardedVehicles++;
      } else {
        break; // next vehicle doesn’t fit; stop boarding
      }
    }

    totalVehicles += boardedVehicles;
    totalSeatsUsed += seatsThisRound;
    totalMinutes += INTERVAL;

    return boardedVehicles > 0;
  }

  DinString convertToString() const {
    if (state == FerryState::OPEN) {
      return DinString("OPEN");
    } else {
      return DinString("CLOSED");
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const Ferry &ferry) {
    os << "Vehicle type: ";
    switch (TYPE) {
    case VehicleType::CAR:
      os << "CAR";
      break;
    case VehicleType::BUS:
      os << "BUS";
      break;
    case VehicleType::TRUCK:
      os << "TRUCK";
      break;
    case VehicleType::BIKE:
      os << "BIKE";
      break;
    }

    os << "\nFerry State: " << ferry.convertToString();
    os << "\nCapacity (seats): " << CAPACITY;
    os << "\nFerry travel time: " << INTERVAL;
    os << "\nTotal vehicles boarded: " << ferry.totalVehicles;
    os << "\nTotal seats used: " << ferry.totalSeatsUsed;
    os << "\nTotal travel time(hours): " << ferry.totalMinutes / 60.0f;

    if (!ferry.queue.empty()) {
      os << "\nQueue: ";

      for (int i = 1; i <= ferry.queue.size(); i++) {
        Vehicle *v;

        ferry.queue.read(i, v);
        os << "\n - " << *v;
      }
    }

    os << "\n------------";

    return os;
  }
};