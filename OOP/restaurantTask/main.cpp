#include "restaurant.hpp"
#include <ctime>
#include <iostream>

int main() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  std::cout << "=== TESTING RESERVATION ===\n";
  Reservation r1;                                   // default
  Reservation r2(101, MealType::LUNCH, "Alice", 3); // param
  Reservation r3(r2);                               // copy

  r1.print();
  r2.print();
  r3.print();

  r3.setNumPeople(5);
  std::cout << "Updated r3 guests -> " << r3.getNumPeople() << "\n";

  std::cout << "\n=== TESTING RESTAURANT ===\n";
  Restaurant rest("Mountain View Bistro", 10); // name, number of tables

  // initial print
  rest.print();

  // Make some reservations
  Reservation resA(201, MealType::DINNER, "Bob", 4);
  Reservation resB(202, MealType::DINNER, "Charlie", 2);
  Reservation resC(203, MealType::BREAKFAST, "Diana", 3);
  Reservation resD(204, MealType::DINNER, "Eve", 6);
  Reservation resE(205, MealType::LUNCH, "Frank", 7);
  Reservation resF(206, MealType::DINNER, "Grace", 5);
  Reservation resG(207, MealType::DINNER, "Heidi", 2);

  // Two extra dinner reservations to guarantee hitting >5 tables
  Reservation resH(208, MealType::DINNER, "Ivan", 1);
  Reservation resI(209, MealType::DINNER, "Judy", 2);

  rest.makeReservation(&resA);
  rest.makeReservation(&resB);
  rest.makeReservation(&resC);
  rest.makeReservation(&resD);
  rest.makeReservation(&resE);
  rest.makeReservation(&resF);
  rest.makeReservation(&resG);
  rest.makeReservation(&resH);
  rest.makeReservation(&resI);

  std::cout << "\nAfter making several reservations:\n";
  rest.print();

  // count per meal
  std::cout << "\nGuests eating at LUNCH: "
            << rest.countGuestsEating(MealType::LUNCH) << "\n";
  std::cout << "Guests eating at DINNER: "
            << rest.countGuestsEating(MealType::DINNER) << "\n";
  std::cout << "Guests eating at BREAKFAST: "
            << rest.countGuestsEating(MealType::BREAKFAST) << "\n";

  // clear all tables
  rest.clearAllTables();
  std::cout << "\nAfter clearing all tables:\n";
  rest.print();

  return 0;
}