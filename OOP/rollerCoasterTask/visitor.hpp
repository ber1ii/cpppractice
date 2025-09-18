#pragma once
#include "rideTicket.hpp"

class Visitor {
private:
  RideTicket ticket;
  DinString id;
  DinString name;

public:
  Visitor() : ticket(), id(""), name("") {}
  Visitor(int ticketNumber, RideType type, const DinString &id,
          const DinString &name)
      : ticket(ticketNumber, type), id(id), name(name) {}
  DinString getId() const { return id; }
  DinString getName() const { return name; }
  RideType getRideType() const { return ticket.getRideType(); }

  virtual DinString toString() const { return id + " " + name; }

  friend std::ostream &operator<<(std::ostream &os, const Visitor &v) {
    os << v.toString() << " | " << v.ticket;
    return os;
  }

  virtual ~Visitor() {}
};