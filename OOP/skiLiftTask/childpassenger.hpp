#pragma once
#include "passenger.hpp"

class ChildPassenger : public Passenger {
private:
  DinString parentSSN;

public:
  // Default constructor
  ChildPassenger() : Passenger(), parentSSN("") {}

  // Parameterized constructor
  ChildPassenger(int ticketNumber, TicketType type, const DinString &ssn,
                 const DinString &name, const DinString &parentSSN)
      : Passenger(ticketNumber, type, ssn, name), parentSSN(parentSSN) {}

  ChildPassenger(const Passenger &parent, const DinString &parentSSN)
      : Passenger(parent), parentSSN(parentSSN) {}

  DinString toString() const override {
    DinString ret = "Child: ";
    ret += Passenger::toString();
    ret += " Parent: ";
    ret += parentSSN;

    return ret;
  }

  ~ChildPassenger() override {}
};