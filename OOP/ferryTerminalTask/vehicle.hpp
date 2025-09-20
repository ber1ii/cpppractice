#pragma once
#include "ferryTicket.hpp"

class Vehicle {
private:
  FerryTicket ticket;
  DinString id;
  DinString name;
  int seatsRequired; // number of ferry seats required for specific vehicle
public:
  Vehicle() : ticket(), id(""), name(""), seatsRequired(0) {}
  Vehicle(int ticketNumber, VehicleType type, const DinString &id,
          const DinString &name, int seatsRequired)
      : ticket(ticketNumber, type), id(id), name(name),
        seatsRequired(seatsRequired) {}

  DinString getId() const { return id; }
  VehicleType getVehicleType() const { return ticket.getVehicleType(); }
  int getSeatsRequired() const { return seatsRequired; }

  virtual DinString toString() const {
    return DinString("ID: ") + id + ", Owner name: " + name +
           ", Seats required: " +
           DinString(std::to_string(seatsRequired).c_str());
  }

  friend std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle) {
    os << vehicle.toString() << " | " << vehicle.ticket;

    return os;
  }

  virtual ~Vehicle() {}
};