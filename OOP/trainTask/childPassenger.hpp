#pragma once
#include "passenger.hpp"

class ChildPassenger : public Passenger {
private:
  DinString guardianId;

public:
  ChildPassenger() : Passenger(), guardianId("") {}
  ChildPassenger(int ticketNumber, RouteType type, const DinString &id,
                 const DinString &name, int age, const DinString &guardianId)
      : Passenger(ticketNumber, type, id, name, age), guardianId(guardianId) {}
  ChildPassenger(const Passenger &p, const DinString &guardianId)
      : Passenger(p), guardianId(guardianId) {}

  DinString getGuardianId() const { return guardianId; }

  DinString toString() const override {
    DinString ret;
    ret = "Child: ";
    ret += Passenger::toString();
    ret += " Guardian ID: ";
    ret += guardianId;

    return ret;
  }

  ~ChildPassenger() {}
};