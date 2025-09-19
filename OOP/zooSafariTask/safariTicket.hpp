#pragma once

#include "dinstring.hpp"

enum class AnimalType { CARNIVORE, HERBIVORE, BIRD };

class SafariTicket {
private:
  int ticketNumber;
  AnimalType type;

public:
  SafariTicket() : ticketNumber(0), type(AnimalType::CARNIVORE) {}
  SafariTicket(int ticketNumber, AnimalType type)
      : ticketNumber(ticketNumber), type(type) {}

  int getTicketNumber() const { return ticketNumber; }
  AnimalType getAnimalType() const { return type; }

  DinString convertToString(AnimalType type) const {
    switch (type) {
    case AnimalType::CARNIVORE:
      return DinString("CARNIVORE");
    case AnimalType::HERBIVORE:
      return DinString("HERBIVORE");
    case AnimalType::BIRD:
      return DinString("BIRD");
    }

    return DinString("UNKNOWN");
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const SafariTicket &ticket) {
    os << "Ticket number:" << ticket.ticketNumber
       << " | Ticket type: " << ticket.convertToString(ticket.type);
    return os;
  }
};