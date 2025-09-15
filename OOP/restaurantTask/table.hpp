#pragma once
#include "reservation.hpp"
#include <string>

class Table {
private:
  int id;
  int capacity;
  bool occupied;
  Reservation *currentReservation;

public:
  Table(int id = 0, int cap = 0, bool status = false,
        Reservation *cRes = nullptr)
      : id(id), capacity(cap), occupied(status), currentReservation(cRes) {}

  Reservation *getReservation() const { return currentReservation; }
  bool isOccupied() const { return occupied; }

  bool assignReservation(Reservation *r) {
    if (occupied == false && r != nullptr && r->getNumPeople() <= capacity) {
      occupied = true;
      currentReservation = r;
      return true;
    }
    return false;
  }

  void clearTable() {
    if (occupied == true && currentReservation != nullptr) {
      occupied = false;
      currentReservation = nullptr;
    }
  }

  std::string occupancyToString(bool occupied) const {
    if (occupied) {
      return "occupied";
    } else {
      return "empty";
    }
  }

  void print() const {
    std::cout << "Table ID: " << id << ", capacity: " << capacity
              << ", occupancy " << occupancyToString(occupied) << std::endl;

    if (currentReservation != nullptr) {
      std::cout << "Reservation ->";
      currentReservation->print();
    } else {
      std::cout << "Reservation -> None" << std::endl;
    }
  }

  ~Table() { currentReservation = nullptr; }
};