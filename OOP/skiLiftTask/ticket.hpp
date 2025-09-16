#pragma once
#include <iostream>
#include <string>

enum class TicketType { SUMMER, SKI, SKI_OPENING };

class Ticket {
private:
  int ticketNumber;
  TicketType type;

public:
  Ticket(int tN, TicketType t) : ticketNumber(tN), type(t) {}
  Ticket() : ticketNumber(0), type(TicketType::SKI) {}

  int getTicket() const { return ticketNumber; }
  TicketType getTicketType() const { return type; }

  std::string convertTicketTypeToString(TicketType type) const {
    switch (type) {
    case TicketType::SUMMER:
      return "SUMMER";
    case TicketType::SKI:
      return "SKI";
    case TicketType::SKI_OPENING:
      return "SKI OPENING";
    }

    return "UNKNOWN";
  }

  // Friend because it needs direct access
  friend std::ostream &operator<<(std::ostream &os, const Ticket &t) {
    os << "Ticket number: " << t.ticketNumber
       << ", Type: " << t.convertTicketTypeToString(t.type);
    return os;
  }
};