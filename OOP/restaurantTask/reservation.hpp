#pragma once
#include <iostream>
#include <string>

enum class MealType { BREAKFAST, LUNCH, DINNER };

class Reservation {
private:
  int id;
  MealType meal;
  std::string customerName;
  int numPeople;

public:
  Reservation(int id = 0, MealType type = MealType::BREAKFAST,
              std::string s = "n/A", int n = 0)
      : id(id), meal(type), customerName(s), numPeople(n) {}
  Reservation(const Reservation &r)
      : id(r.id), meal(r.meal), customerName(r.customerName),
        numPeople(r.numPeople) {}

  int getID() const { return id; }
  MealType getMeal() const { return meal; }
  std::string getCustomerName() const { return customerName; }
  int getNumPeople() const { return numPeople; }

  void setNumPeople(int n) { numPeople = n; }

  static std::string convertEnumToString(MealType meal) {
    switch (meal) {
    case MealType::BREAKFAST:
      return "BREAKFAST";
    case MealType::LUNCH:
      return "LUNCH";
    case MealType::DINNER:
      return "DINNER";
    }

    return "UNKNOWN";
  }

  void print() const {
    std::cout << "Reservation ID: " << id
              << " , Meal Type: " << convertEnumToString(meal)
              << ", Customer Name: " << customerName
              << ", number of guests: " << numPeople << std::endl;
  }
};