#pragma once
#include "vehicle.hpp"

class MiniBus : public Vehicle {
private:
  DinString groupLeaderId;

public:
  MiniBus() : Vehicle(), groupLeaderId("") {}
  MiniBus(int ticketNumber, VehicleType type, const DinString &id,
          const DinString &name, int seatsRequired,
          const DinString &groupLeaderId)
      : Vehicle(ticketNumber, type, id, name, seatsRequired),
        groupLeaderId(groupLeaderId) {}
  MiniBus(const Vehicle &v, const DinString &groupLeaderId)
      : Vehicle(v), groupLeaderId(groupLeaderId) {}

  DinString getGroupLeaderId() const { return groupLeaderId; }

  DinString toString() const override {
    DinString ret;
    ret = "MiniBus: ";
    ret += Vehicle::toString();
    ret += " Leader ID: ";
    ret += groupLeaderId;

    return ret;
  }

  ~MiniBus() {}
};