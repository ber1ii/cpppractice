#include "childVisitor.hpp"
#include "safariRide.hpp"
#include <iostream>

int main() {
  // 1. Test CARNIVORE SafariRide (capacity=3 seats, 20 min duration)
  SafariRide<AnimalType::CARNIVORE, 3, 20> carnivoreSafari;
  carnivoreSafari.open();

  Visitor alice(1, AnimalType::CARNIVORE, DinString("A1"), DinString("Alice"),
                30);
  Visitor teen(2, AnimalType::CARNIVORE, DinString("T1"), DinString("Tom"),
               15); // too young
  ChildVisitor child1(3, AnimalType::CARNIVORE, DinString("C1"),
                      DinString("Cathy"), 10, DinString("A1"));
  ChildVisitor orphan(4, AnimalType::CARNIVORE, DinString("C2"),
                      DinString("Orphan"), 9, DinString("NOPE"));

  std::cout << "Add Alice (adult 30): "
            << (carnivoreSafari.addVisitor(&alice) ? "OK" : "FAIL") << "\n";

  std::cout << "Add Tom (teen 15): "
            << (carnivoreSafari.addVisitor(&teen) ? "OK" : "FAIL") << "\n";

  std::cout << "Add Cathy (child 10, parent Alice): "
            << (carnivoreSafari.addVisitor(&child1) ? "OK" : "FAIL") << "\n";

  std::cout << "Add Orphan (child 9, no parent): "
            << (carnivoreSafari.addVisitor(&orphan) ? "OK" : "FAIL") << "\n";

  std::cout << "\n--- Carnivore Safari before ride ---\n";
  std::cout << carnivoreSafari << "\n\n";

  carnivoreSafari.runRide();

  std::cout << "--- Carnivore Safari after one ride ---\n";
  std::cout << carnivoreSafari << "\n\n";

  // 2. Test HERBIVORE SafariRide (no age restriction!)
  SafariRide<AnimalType::HERBIVORE, 2, 15> herbivoreSafari;
  herbivoreSafari.open();

  Visitor adult2(5, AnimalType::HERBIVORE, DinString("H1"), DinString("Henry"),
                 40);
  Visitor teen2(6, AnimalType::HERBIVORE, DinString("HT1"), DinString("Teo"),
                14); // allowed here
  ChildVisitor child2(7, AnimalType::HERBIVORE, DinString("HC1"),
                      DinString("Lilly"), 7, DinString("H1"));

  herbivoreSafari.addVisitor(&adult2);
  herbivoreSafari.addVisitor(&teen2);
  herbivoreSafari.addVisitor(&child2);

  std::cout << "--- Herbivore Safari before ride ---\n";
  std::cout << herbivoreSafari << "\n\n";

  herbivoreSafari.runRide();

  std::cout << "--- Herbivore Safari after one ride ---\n";
  std::cout << herbivoreSafari << "\n\n";

  // 3. Test BIRD SafariRide with over-capacity queue
  SafariRide<AnimalType::BIRD, 2, 10> birdSafari;
  birdSafari.open();

  Visitor b1(8, AnimalType::BIRD, DinString("B1"), DinString("Ana"), 22);
  Visitor b2(9, AnimalType::BIRD, DinString("B2"), DinString("Milo"), 25);
  Visitor b3(10, AnimalType::BIRD, DinString("B3"), DinString("Zoe"), 18);

  birdSafari.addVisitor(&b1);
  birdSafari.addVisitor(&b2);
  birdSafari.addVisitor(&b3);

  std::cout << "--- Bird Safari before ride ---\n";
  std::cout << birdSafari << "\n\n";

  birdSafari.runRide(); // seats=2 -> leaves one waiting!

  std::cout << "--- Bird Safari after first ride ---\n";
  std::cout << birdSafari << "\n\n";

  birdSafari.runRide(); // second ride takes last one

  std::cout << "--- Bird Safari after second ride ---\n";
  std::cout << birdSafari << "\n\n";

  return 0;
}