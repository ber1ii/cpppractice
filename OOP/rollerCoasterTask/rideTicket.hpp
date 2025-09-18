#pragma once
#include "dinstring.hpp"
#include <iostream>

enum class RideType { THRILL, FAMILY, KIDS };

class RideTicket {
private:
  int ticketNumber;
  RideType type;

public:
  RideTicket() : ticketNumber(0), type(RideType::KIDS) {}
  RideTicket(int tN, RideType t) : ticketNumber(tN), type(t) {}

  int getTicketNumber() const { return ticketNumber; }
  RideType getRideType() const { return type; }

  DinString convertRideTypeToString(RideType type) const {
    switch (type) {
    case RideType::THRILL:
      return DinString("THRILL");
    case RideType::FAMILY:
      return DinString("FAMILY");
    case RideType::KIDS:
      return DinString("KIDS");
    }
    return DinString("UNKNOWN");
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const RideTicket &rideTicket) {
    os << "Ticket number: " << rideTicket.ticketNumber
       << " Ride Type: " << rideTicket.convertRideTypeToString(rideTicket.type);
    return os;
  }
};