#pragma once
#include "fan.hpp"

class ChildFan : public Fan {
private:
  DinString guardianId;

public:
  ChildFan() : Fan(), guardianId("") {}
  ChildFan(int ticketNumber, MatchType type, const DinString &id,
           const DinString &name, int age, const DinString &guardianId)
      : Fan(ticketNumber, type, id, name, age), guardianId(guardianId) {}
  ChildFan(const Fan &fan, const DinString &guardianId)
      : Fan(fan), guardianId(guardianId) {}

  DinString getGuardianId() const { return guardianId; }

  DinString toString() const override {
    DinString ret;
    ret = "Child: ";
    ret += Fan::toString();
    ret += " Guardian: ";
    ret += guardianId;

    return ret;
  }

  ~ChildFan() {}
};