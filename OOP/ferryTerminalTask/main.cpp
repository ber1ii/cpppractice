#include "ferry.hpp"
#include "miniBus.hpp"
#include <iostream>

int main() {
  // Create ferry for CAR type, capacity 10 seats, departure interval 30 min
  Ferry<VehicleType::CAR, 10, 30> carFerry;
  carFerry.open();

  // Vehicles
  Vehicle car1(1, VehicleType::CAR, DinString("C1"), DinString("Alice"), 2);
  Vehicle car2(2, VehicleType::CAR, DinString("C2"), DinString("Bob"), 4);
  Vehicle car3(3, VehicleType::CAR, DinString("C3"), DinString("Charlie"),
               6); // won't fit if not enough space

  MiniBus minibus1(4, VehicleType::CAR, DinString("M1"), DinString("GroupA"), 5,
                   DinString("C1"));
  MiniBus orphanBus(5, VehicleType::CAR, DinString("M2"), DinString("Orphans"),
                    5, DinString("NOPE"));

  Vehicle truckWrongType(6, VehicleType::TRUCK, DinString("T1"),
                         DinString("John"), 8);

  // Add vehicles
  std::cout << "Add Car1 (2 seats): "
            << (carFerry.addVehicle(&car1) ? "OK" : "FAIL") << "\n";

  std::cout << "Add Car2 (4 seats): "
            << (carFerry.addVehicle(&car2) ? "OK" : "FAIL") << "\n";

  std::cout << "Add Car3 (6 seats): "
            << (carFerry.addVehicle(&car3) ? "OK" : "FAIL") << "\n";

  std::cout << "Add Minibus1 (leader=C1 in queue): "
            << (carFerry.addVehicle(&minibus1) ? "OK" : "FAIL") << "\n";

  std::cout << "Add OrphanBus (leader missing): "
            << (carFerry.addVehicle(&orphanBus) ? "OK" : "FAIL (as expected)")
            << "\n";

  std::cout << "Add TruckWrongType (not CAR): "
            << (carFerry.addVehicle(&truckWrongType) ? "OK"
                                                     : "FAIL (as expected)")
            << "\n";

  std::cout << "\n--- CarFerry BEFORE departure ---\n";
  std::cout << carFerry << "\n\n";

  // First departure (CAP=10)
  carFerry.depart();
  std::cout << "--- CarFerry AFTER 1st departure ---\n";
  std::cout << carFerry << "\n\n";

  // Add filler more vehicles for second round
  Vehicle car4(7, VehicleType::CAR, DinString("C4"), DinString("David"), 3);
  Vehicle car5(8, VehicleType::CAR, DinString("C5"), DinString("Eva"), 3);
  Vehicle car6(9, VehicleType::CAR, DinString("C6"), DinString("Frank"), 3);

  carFerry.addVehicle(&car4);
  carFerry.addVehicle(&car5);
  carFerry.addVehicle(&car6);

  std::cout << "--- CarFerry BEFORE 2nd departure ---\n";
  std::cout << carFerry << "\n\n";

  carFerry.depart();
  std::cout << "--- CarFerry AFTER 2nd departure ---\n";
  std::cout << carFerry << "\n\n";

  return 0;
}