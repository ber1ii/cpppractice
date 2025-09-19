#pragma once
#include "childPassenger.hpp"
#include "list.hpp"
#include "passenger.hpp"

enum class TrainState { OPEN, CLOSED };

template <RouteType TYPE, int SEATS, int INTERVAL> class Train {
private:
  List<Passenger *> queue;
  TrainState state;
  int totalPassengers;
  int totalMinutes;

public:
  Train() : state(TrainState::CLOSED), totalPassengers(0), totalMinutes(0) {}

  void open() {
    state = TrainState::OPEN;
    totalPassengers = 0;
    totalMinutes = 0;
  }

  void close() {
    state = TrainState::CLOSED;
    queue.clear();
  }

  bool addPassenger(Passenger *p) {
    if (p->getRouteType() != TYPE) {
      return false;
    }

    for (int i = 1; i <= queue.size(); i++) {
      Passenger *existing;

      queue.read(i, existing);
      if (existing->getId() == p->getId()) {
        return false;
      }
    }

    ChildPassenger *cp = dynamic_cast<ChildPassenger *>(p);

    if (cp != nullptr) {
      bool guardianFound = false;
      for (int i = 1; i <= queue.size(); i++) {
        Passenger *potentialGuardian;

        queue.read(i, potentialGuardian);

        if (cp->getGuardianId() == potentialGuardian->getId()) {
          guardianFound = true;
          break;
        }
      }

      if (!guardianFound) {
        return false;
      }
    } else {
      if (TYPE == RouteType::EXPRESS && p->getAge() < 18) {
        return false;
      }
    }

    queue.add(queue.size() + 1, p);
    return true;
  }

  int queueSize() const { return queue.size(); }

  bool depart() {
    if (state == TrainState::CLOSED || queue.empty()) {
      return false;
    }

    int passengersOnCurrentTrain = std::min(SEATS, queue.size());

    for (int i = 0; i < passengersOnCurrentTrain; i++) {
      queue.remove(1);
    }

    totalPassengers += passengersOnCurrentTrain;
    totalMinutes += INTERVAL;

    return true;
  }

  DinString convertToString() const {
    if (state == TrainState::OPEN) {
      return DinString("OPEN");
    } else {
      return DinString("CLOSED");
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const Train &train) {
    os << "Route type: ";
    switch (TYPE) {
    case RouteType::LOCAL:
      os << DinString("LOCAL");
      break;
    case RouteType::INTERCITY:
      os << DinString("INTERCITY");
      break;
    case RouteType::EXPRESS:
      os << DinString("EXPRESS");
      break;
    }

    os << "\nTotal seats on train: " << SEATS;
    os << "\nInterval per ride: " << INTERVAL;
    os << "\nTrain state: " << train.convertToString();
    os << "\nTotal passengers: " << train.totalPassengers;
    os << "\nTotal train runtime(hours): " << train.totalMinutes / 60.0f;

    if (!train.queue.empty()) {
      os << "\nQueue: ";
      for (int i = 1; i <= train.queue.size(); i++) {
        Passenger *p;

        train.queue.read(i, p);
        os << "\n - " << *p;
      }
    }

    os << "\n------------";

    return os;
  }
};