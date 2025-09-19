#pragma once
#include "trainTicket.hpp"

class Passenger {
private:
  TrainTicket ticket;
  DinString id;
  DinString name;
  int age;

public:
  Passenger() : ticket(), id(""), name(""), age(0) {}
  Passenger(int ticketNumber, RouteType type, const DinString &id,
            const DinString &name, int age)
      : ticket(ticketNumber, type), id(id), name(name), age(age) {}

  DinString getId() const { return id; }
  RouteType getRouteType() const { return ticket.getRouteType(); }
  int getAge() const { return age; }

  virtual DinString toString() const {
    return "ID: " + id + " Name: " + name +
           " Age: " + DinString(std::to_string(age).c_str());
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const Passenger &passenger) {
    os << passenger.toString() << " | " << passenger.ticket;

    return os;
  }

  virtual ~Passenger() {}
};