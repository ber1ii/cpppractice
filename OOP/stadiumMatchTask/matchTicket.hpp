#pragma once
#include "dinstring.hpp"

enum class MatchType { FOOTBALL, BASKETBALL, TENNIS };

class MatchTicket {
private:
  int ticketNumber;
  MatchType type;

public:
  MatchTicket() : ticketNumber(0), type(MatchType::TENNIS) {}
  MatchTicket(int ticketNumber, MatchType type)
      : ticketNumber(ticketNumber), type(type) {}

  int getTicketNumber() const { return ticketNumber; }
  MatchType getMatchType() const { return type; }

  DinString convertToString() const {
    switch (type) {
    case MatchType::FOOTBALL:
      return DinString("FOOTBALL");
    case MatchType::BASKETBALL:
      return DinString("BASKETBALL");
    case MatchType::TENNIS:
      return DinString("TENNIS");
    }
    return DinString("UNKNOWN");
  }

  friend std::ostream &operator<<(std::ostream &os, const MatchTicket &ticket) {
    os << "Ticket Number: " << ticket.ticketNumber
       << " , Match Type: " << ticket.convertToString();

    return os;
  }
};