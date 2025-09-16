#pragma once
#include "movieTicket.hpp"

class Visitor {
private:
  MovieTicket ticket;
  DinString id;
  DinString name;

public:
  Visitor() : ticket(), id(""), name("") {}
  Visitor(int ticketNumber, MovieType type, const DinString &id,
          const DinString &name)
      : ticket(ticketNumber, type), id(id), name(name) {}

  DinString getID() const { return id; }
  MovieType getMovieType() const { return ticket.getMovieType(); }

  virtual DinString toString() const { return id + " " + name; }

  friend std::ostream &operator<<(std::ostream &os, const Visitor &v) {
    os << v.toString() << " | " << v.ticket;
    return os;
  }

  virtual ~Visitor() {}
};