#include "childPassenger.hpp"
#include "train.hpp"
#include <iostream>

int main() {
  // Create an EXPRESS train with 3 seats per departure, interval = 20 minutes
  Train<RouteType::EXPRESS, 3, 20> expressTrain;
  expressTrain.open();

  // Passengers
  Passenger alice(1, RouteType::EXPRESS, DinString("P1"), DinString("Alice"),
                  25);
  Passenger bob(2, RouteType::EXPRESS, DinString("P2"), DinString("Bob"),
                16); // too young
  ChildPassenger charlie(3, RouteType::EXPRESS, DinString("C1"),
                         DinString("Charlie"), 10,
                         DinString("P1")); // child of Alice
  ChildPassenger orphan(4, RouteType::EXPRESS, DinString("C2"),
                        DinString("Orphan"), 10, DinString("NOPE")); // orphan
  Passenger wrongRoute(5, RouteType::INTERCITY, DinString("P3"),
                       DinString("Mark"), 30); // wrong route type

  // Test adding
  std::cout << "Add Alice (25, EXPRESS): "
            << (expressTrain.addPassenger(&alice) ? "OK" : "FAIL") << "\n";

  std::cout << "Add Bob (16, EXPRESS): "
            << (expressTrain.addPassenger(&bob) ? "OK" : "FAIL")
            << " (should FAIL)\n";

  std::cout << "Add Charlie (10, EXPRESS child, guardian=P1): "
            << (expressTrain.addPassenger(&charlie) ? "OK" : "FAIL") << "\n";

  std::cout << "Add Orphan (10, EXPRESS child, guardian missing): "
            << (expressTrain.addPassenger(&orphan) ? "OK" : "FAIL")
            << " (should FAIL)\n";

  std::cout << "Add WrongRoute (30, INTERCITY): "
            << (expressTrain.addPassenger(&wrongRoute) ? "OK" : "FAIL")
            << " (should FAIL)\n";

  std::cout << "\n--- EXPRESS Train Before Departure ---\n";
  std::cout << expressTrain << "\n\n";

  // Run first departure
  expressTrain.depart();

  std::cout << "--- EXPRESS Train After 1st Departure ---\n";
  std::cout << expressTrain << "\n\n";

  // Add more EXPRESS passengers to test multiple departures
  Passenger dave(6, RouteType::EXPRESS, DinString("P4"), DinString("Dave"), 40);
  Passenger eva(7, RouteType::EXPRESS, DinString("P5"), DinString("Eva"), 29);
  Passenger frank(8, RouteType::EXPRESS, DinString("P6"), DinString("Frank"),
                  22);
  Passenger gina(9, RouteType::EXPRESS, DinString("P7"), DinString("Gina"), 31);

  expressTrain.addPassenger(&dave);
  expressTrain.addPassenger(&eva);
  expressTrain.addPassenger(&frank);
  expressTrain.addPassenger(&gina);

  std::cout << "--- EXPRESS Train After Boarding 4 More ---\n";
  std::cout << expressTrain << "\n\n";

  // Run second departure (capacity=3, so 3 board, Gina remains)
  expressTrain.depart();
  std::cout << "--- EXPRESS Train After 2nd Departure ---\n";
  std::cout << expressTrain << "\n\n";

  // Run third departure (should take Gina alone)
  expressTrain.depart();
  std::cout << "--- EXPRESS Train After 3rd Departure ---\n";
  std::cout << expressTrain << "\n\n";

  return 0;
}