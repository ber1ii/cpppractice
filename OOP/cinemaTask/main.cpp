#include "childVisitor.hpp"
#include "cinema.hpp"
#include <iostream>

int main() {
  // Create a Cinema hall: ACTION movies, 3 seats, runtime 120 min
  Cinema<MovieType::ACTION, 3, 120> hall;
  hall.open();

  // Visitors
  Visitor v1(1, MovieType::ACTION, DinString("A111"), DinString("John"));
  ChildVisitor c1(2, MovieType::ACTION, DinString("A222"), DinString("Anna"),
                  DinString("A111"));
  Visitor v2(3, MovieType::ACTION, DinString("A333"), DinString("Marko"));
  Visitor wrongGuy(4, MovieType::COMEDY, DinString("C111"), DinString("Petar"));

  // Add valid visitors
  hall.addVisitor(&v1);
  hall.addVisitor(&c1);
  hall.addVisitor(&v2);

  std::cout << "--- After adding John, Anna, and Marko ---\n";
  std::cout << hall << "\n\n";

  // Screening 1
  hall.runScreening();
  std::cout << "--- After first screening ---\n";
  std::cout << hall << "\n\n";

  // Try adding wrong genre
  if (!hall.addVisitor(&wrongGuy)) {
    std::cout << "Petar REJECTED (wrong movie type)\n\n";
  }

  // Add more visitors
  Visitor v3(5, MovieType::ACTION, DinString("A444"), DinString("Milos"));
  Visitor v4(6, MovieType::ACTION, DinString("A555"), DinString("Ana"));
  hall.addVisitor(&v3);
  hall.addVisitor(&v4);

  std::cout << "--- After adding Milos and Ana ---\n";
  std::cout << hall << "\n\n";

  // Screening 2
  hall.runScreening();
  std::cout << "--- After second screening ---\n";
  std::cout << hall << "\n";

  return 0;
}