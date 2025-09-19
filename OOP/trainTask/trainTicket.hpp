#pragma once
#include "dinstring.hpp"

enum class RouteType { LOCAL, INTERCITY, EXPRESS };

class TrainTicket {
private:
  int ticketNumber;
  RouteType type;

public:
  TrainTicket() : ticketNumber(0), type(RouteType::LOCAL) {}
  TrainTicket(int ticketNumber, RouteType type)
      : ticketNumber(ticketNumber), type(type) {}

  int getTicketNumber() const { return ticketNumber; }
  RouteType getRouteType() const { return type; }

  DinString convertToString() const {
    switch (type) {
    case RouteType::LOCAL:
      return DinString("LOCAL");
    case RouteType::INTERCITY:
      return DinString("INTERCITY");
    case RouteType::EXPRESS:
      return DinString("EXPRESS");
    }

    return DinString("UNKNOWN");
  }

  friend std::ostream &operator<<(std::ostream &os, const TrainTicket &track) {
    os << "Ticket number: " << track.ticketNumber
       << " Ticket Type: " << track.convertToString();

    return os;
  }
};