#pragma once
#include "dinstring.hpp"
#include "list.hpp"
#include "passenger.hpp"
#include <iostream>

enum class LiftState { OPEN, CLOSED };

template <TicketType SEASON, int SEATS, int INTERVAL> class SkiLift {
private:
  List<Passenger *> waitingPassengers;
  LiftState state;
  int totalRides;
  int totalMinutes;

public:
  SkiLift() : state(LiftState::CLOSED), totalRides(0), totalMinutes(0) {}

  void open() {
    state = LiftState::OPEN;
    totalRides = 0;
    totalMinutes = 0;
  }

  void close() {
    state = LiftState::CLOSED;
    waitingPassengers.clear();
  }

  bool addPassenger(Passenger *p) {
    // Wrong season ticket check
    if (p->getTicketType() != SEASON) {
      return false;
    }

    // Check duplicates by SSN(JMBG)
    for (int i = 1; i <= waitingPassengers.size(); i++) {
      Passenger *existing;

      waitingPassengers.read(i, existing);
      if (existing->getSSN() == p->getSSN()) {
        return false;
      }
    }

    waitingPassengers.add(waitingPassengers.size() + 1, p);
    return true;
  }

  int passengerCount() const { return waitingPassengers.size(); }

  bool transportRound() {
    if (state == LiftState::CLOSED) {
      return false;
    }
    if (waitingPassengers.empty()) {
      return false;
    }

    int passengersThisRound = std::min(SEATS, waitingPassengers.size());

    // Remove first N passengers
    for (int i{}; i < passengersThisRound; i++) {
      Passenger *p;
      waitingPassengers.read(1, p);
      waitingPassengers.remove(1);
    }

    totalRides += passengersThisRound;
    totalMinutes += INTERVAL;

    return true;
  }

  DinString liftStateToString(LiftState state) const {
    if (state == LiftState::OPEN) {
      return "OPEN";
    } else {
      return "CLOSED";
    }

    return "UNKNOWN";
  }

  friend std::ostream &operator<<(std::ostream &os, const SkiLift &lift) {
    os << "--- SkiLift ---\n";
    os << "Season: ";
    switch (SEASON) {
    case TicketType::SUMMER:
      os << "SUMMER";
      break;
    case TicketType::SKI:
      os << "SKI";
      break;
    case TicketType::SKI_OPENING:
      os << "SKI OPENING";
      break;
    }

    os << "\nSeats per ride: " << SEATS << "\nInterval: " << INTERVAL
       << "\nState: " << lift.liftStateToString(lift.state)
       << "\nTotal passengers transported: " << lift.totalRides
       << "\nTotal working time(hours): "
       << static_cast<float>((static_cast<float>(lift.totalMinutes) / 60))
       << "\nPassengers waiting: " << lift.waitingPassengers.size();

    if (!lift.waitingPassengers.empty()) {
      os << "\nQueue: ";
      for (int i = 1; i <= lift.waitingPassengers.size(); i++) {
        Passenger *p;
        lift.waitingPassengers.read(i, p);
        os << "\n - " << *p;
      }
    }

    os << "\n---------\n";
    return os;
  }
};