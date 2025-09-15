#pragma once
#include "table.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class Restaurant {
private:
  std::string name;
  std::vector<Table> tables;

public:
  Restaurant(std::string name, int numberTables) : name(name) {
    tables.reserve(numberTables);

    for (int i{}; i < numberTables; ++i) {
      int randomCap = 2 + (std::rand() % 7);
      tables.emplace_back(i, randomCap);
    }
  }

  bool makeReservation(Reservation *r) {
    for (int i{}; i < tables.size(); i++) {
      if (tables[i].assignReservation(r)) {
        std::cout << "Successful reservation!" << std::endl;
        return true;
      }
    }
    return false;
  }

  void clearAllTables() {
    for (auto &t : tables) {
      t.clearTable();
    }
  }

  int countGuestsEating(MealType meal) {
    int count{};

    for (int i{}; i < tables.size(); i++) {
      if (tables[i].isOccupied()) {
        Reservation *r = tables[i].getReservation();
        if (r != nullptr && r->getMeal() == meal) {
          count += r->getNumPeople();
        }
      }
    }

    return count;
  }

  int countOccupiedTablesAtDinner() const {
    int count{};

    for (int i{}; i < tables.size(); i++) {
      if (tables[i].isOccupied()) {
        Reservation *r = tables[i].getReservation();

        if (r->getMeal() == MealType::DINNER) {
          count++;
        }
      }
    }
    return count;
  }

  void print() const {
    int n = countOccupiedTablesAtDinner();

    std::cout << name << ":\n";

    if (n > 5) {
      std::cout << "Happy Hour Discount Activated!" << std::endl;
    }

    for (int i{}; i < tables.size(); i++) {

      tables[i].print();
    }
  }
};