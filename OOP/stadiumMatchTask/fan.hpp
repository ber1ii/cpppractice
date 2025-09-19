#pragma once
#include "matchTicket.hpp"
#include <string>

class Fan {
private:
  MatchTicket ticket;
  DinString id;
  DinString name;
  int age;

public:
  Fan() : ticket(), id(""), name(""), age(0) {}
  Fan(int ticketNumber, MatchType type, const DinString &id,
      const DinString &name, int age)
      : ticket(ticketNumber, type), id(id), name(name), age(age) {}

  DinString getId() const { return id; }
  MatchType getMatchType() const { return ticket.getMatchType(); }
  int getAge() const { return age; }

  virtual DinString toString() const {
    return "ID: " + id + " Name: " + name +
           " Age: " + DinString(std::to_string(age).c_str());
  }

  friend std::ostream &operator<<(std::ostream &os, const Fan &fan) {
    os << fan.toString() << " | " << fan.ticket;

    return os;
  }

  virtual ~Fan() {}
};