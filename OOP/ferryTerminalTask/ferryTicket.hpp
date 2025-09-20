#pragma once
#include "dinstring.hpp"

enum class VehicleType { CAR, TRUCK, BUS, BIKE };

class FerryTicket {
private:
  int ticketNumber;
  VehicleType type;

public:
  FerryTicket() : ticketNumber(0), type(VehicleType::CAR) {}
  FerryTicket(int ticketNumber, VehicleType type)
      : ticketNumber(ticketNumber), type(type) {}

  int getTicketNumber() const { return ticketNumber; }
  VehicleType getVehicleType() const { return type; }

  DinString convertToString() const {
    switch (type) {
    case VehicleType::CAR:
      return DinString("CAR");
    case VehicleType::TRUCK:
      return DinString("TRUCK");
    case VehicleType::BUS:
      return DinString("BUS");
    case VehicleType::BIKE:
      return DinString("BIKE");
    }

    return DinString("UNKNOWN");
  }

  friend std::ostream &operator<<(std::ostream &os, const FerryTicket &ticket) {
    os << "Ticket Number: " << ticket.ticketNumber
       << ", Vehicle Type: " << ticket.convertToString();

    return os;
  }
};