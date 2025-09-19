#pragma once
#include "safariTicket.hpp"
#include <string>

class Visitor {
private:
  SafariTicket ticket;
  DinString id;
  DinString name;
  int age;

public:
  Visitor() : ticket(), id(""), name(""), age(0) {}
  Visitor(int ticketNumber, AnimalType type, const DinString &id,
          const DinString &name, int age)
      : ticket(ticketNumber, type), id(id), name(name), age(age) {}

  DinString getId() const { return id; }
  AnimalType getAnimalType() const { return ticket.getAnimalType(); }
  int getAge() const { return age; }

  virtual DinString toString() const {
    return "ID: " + id + " Name: " + name +
           " Age: " + DinString(std::to_string(age).c_str());
  }

  friend std::ostream &operator<<(std::ostream &os, const Visitor &v) {
    os << v.toString() << " | " << v.ticket;

    return os;
  }

  virtual ~Visitor() {}
};