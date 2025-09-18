#include "childVisitor.hpp"
#include "rollerCoaster.hpp"
#include <iostream>

int main() {
  // 1. Create a RollerCoaster ride
  RollerCoaster<RideType::THRILL, 4, 5> rc;
  rc.open();

  // 2. Create some visitors
  Visitor dad(1, RideType::THRILL, DinString("P1"), DinString("Father"));
  ChildVisitor kid(2, RideType::THRILL, DinString("C1"), DinString("Son"),
                   DinString("P1"));
  ChildVisitor orphan(3, RideType::THRILL, DinString("C2"), DinString("Orphan"),
                      DinString("NOPE"));
  Visitor wrongRide(4, RideType::FAMILY, DinString("P2"),
                    DinString("Bob")); // Wrong type ticket

  // 3. Try adding all of them
  std::cout << "Dad added: " << (rc.addVisitor(&dad) ? "YES" : "NO")
            << "\n"; // YES
  std::cout << "Kid added: " << (rc.addVisitor(&kid) ? "YES" : "NO")
            << "\n"; // YES
  std::cout << "Orphan added: " << (rc.addVisitor(&orphan) ? "YES" : "NO")
            << "\n"; // NO
  std::cout << "Wrong ride ticket added: "
            << (rc.addVisitor(&wrongRide) ? "YES" : "NO") << "\n"; // NO

  // 4. Print rollercoaster before ride
  std::cout << "\n--- Before ride ---\n";
  std::cout << rc << "\n";

  // 5. Run the ride
  rc.runRide();

  // 6. Print rollercoaster after ride
  std::cout << "\n--- After one ride ---\n";
  std::cout << rc << "\n";

  // 7. Add more visitors (test capacity case)
  Visitor v3(5, RideType::THRILL, DinString("P3"), DinString("Alice"));
  Visitor v4(6, RideType::THRILL, DinString("P4"), DinString("Eve"));
  Visitor v5(7, RideType::THRILL, DinString("P5"), DinString("Charlie"));
  Visitor v6(8, RideType::THRILL, DinString("P6"), DinString("Diana"));

  rc.addVisitor(&v3);
  rc.addVisitor(&v4);
  rc.addVisitor(&v5);
  rc.addVisitor(&v6);

  std::cout << "\n--- Queue filled with 4 adults ---\n";
  std::cout << rc << "\n";

  // 8. Run the ride again (should take all 4)
  rc.runRide();

  std::cout << "\n--- After second ride ---\n";
  std::cout << rc << "\n";

  return 0;
}