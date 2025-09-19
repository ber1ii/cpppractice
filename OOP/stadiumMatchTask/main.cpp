#include "childFan.hpp"
#include "stadium.hpp"
#include <iostream>

int main() {
  // ===========================================
  // 1. Test FOOTBALL Stadium (age >= 16)
  // ===========================================
  Stadium<MatchType::FOOTBALL, 3, 120> footballStadium;
  footballStadium.open();

  Fan greg(1, MatchType::FOOTBALL, DinString("01"), DinString("Greg"), 45);
  Fan ben(2, MatchType::FOOTBALL, DinString("02"), DinString("Ben"), 19);
  Fan tooYoung(8, MatchType::FOOTBALL, DinString("08"), DinString("Timmy"),
               14); // too young
  ChildFan gregSon(3, MatchType::FOOTBALL, DinString("03"),
                   DinString("Milivoje"), 10, DinString("01"));
  ChildFan orphan(4, MatchType::FOOTBALL, DinString("04"),
                  DinString("Bruce Wayne"), 9, DinString("NOPE"));

  footballStadium.addFan(&greg);     // adult OK
  footballStadium.addFan(&ben);      // teen OK (≥ 16)
  footballStadium.addFan(&tooYoung); // FAIL (age <16)
  footballStadium.addFan(&gregSon);  // OK, guardian Greg in queue
  footballStadium.addFan(&orphan);   // FAIL (guardian not present)

  std::cout << "\n--- FOOTBALL Stadium before seating ---\n";
  std::cout << footballStadium << "\n\n";

  footballStadium.seatBatch();
  std::cout << "--- FOOTBALL Stadium after 1st batch ---\n";
  std::cout << footballStadium << "\n\n";

  // ===========================================
  // 2. Test BASKETBALL Stadium (no age restriction)
  // ===========================================
  Stadium<MatchType::BASKETBALL, 2, 90> basketballStadium;
  basketballStadium.open();

  Fan alice(5, MatchType::BASKETBALL, DinString("05"), DinString("Alice"),
            12); // allowed
  Fan bob(6, MatchType::BASKETBALL, DinString("06"), DinString("Bob"), 25);
  ChildFan bobSon(7, MatchType::BASKETBALL, DinString("07"), DinString("Chris"),
                  9, DinString("06"));

  basketballStadium.addFan(&alice);
  basketballStadium.addFan(&bob);
  basketballStadium.addFan(&bobSon); // guardian Bob is present

  std::cout << "\n--- BASKETBALL Stadium before seating ---\n";
  std::cout << basketballStadium << "\n\n";

  basketballStadium.seatBatch();
  std::cout << "--- BASKETBALL Stadium after 1st batch ---\n";
  std::cout << basketballStadium << "\n\n";

  basketballStadium.seatBatch();
  std::cout << "--- BASKETBALL Stadium after 2nd batch ---\n";
  std::cout << basketballStadium << "\n\n";

  // ===========================================
  // 3. Test TENNIS Stadium (no age restriction, over capacity queue)
  // ===========================================
  Stadium<MatchType::TENNIS, 2, 60> tennisStadium;
  tennisStadium.open();

  Fan t1(9, MatchType::TENNIS, DinString("09"), DinString("Nole"), 36);
  Fan t2(10, MatchType::TENNIS, DinString("10"), DinString("Rafa"), 37);
  Fan t3(11, MatchType::TENNIS, DinString("11"), DinString("Roger"), 41);

  tennisStadium.addFan(&t1);
  tennisStadium.addFan(&t2);
  tennisStadium.addFan(&t3); // will wait for next batch

  std::cout << "\n--- TENNIS Stadium before seating ---\n";
  std::cout << tennisStadium << "\n\n";

  tennisStadium.seatBatch();
  std::cout << "--- TENNIS Stadium after 1st batch ---\n";
  std::cout << tennisStadium << "\n\n";

  tennisStadium.seatBatch();
  std::cout << "--- TENNIS Stadium after 2nd batch ---\n";
  std::cout << tennisStadium << "\n\n";

  return 0;
}