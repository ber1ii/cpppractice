#pragma once
#include "dinstring.hpp"
#include "ticket.hpp"
#include <iostream>

class Passenger {
private:
  Ticket ticket;
  DinString ssn; // JMBG
  DinString name;

public:
  // Default constructor
  Passenger() : ticket(), ssn(""), name("") {}

  // Parameterized constructor
  Passenger(int ticketNumber, TicketType type, const DinString &s,
            const DinString &n)
      : ticket(ticketNumber, type), ssn(s), name(n) {}

  // Getters
  DinString getSSN() const { return ssn; }
  DinString getName() const { return name; }
  TicketType getTicketType() const { return ticket.getTicketType(); }

  virtual DinString toString() const { return ssn + " " + name; }

  friend std::ostream &operator<<(std::ostream &os, const Passenger &p) {
    os << p.toString() << " | " << p.ticket;
    return os;
  }

  virtual ~Passenger() {}
};