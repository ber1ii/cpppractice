#include "childpassenger.hpp"
#include "dinstring.hpp"
#include "passenger.hpp"
#include "skilift.hpp"
#include "ticket.hpp"
#include <iostream>

int main() {
  // 1. Test ticket
  Ticket t1(101, TicketType::SUMMER);
  Ticket t2(102, TicketType::SKI);
  std::cout << t1 << std::endl;
  std::cout << t2 << std::endl;

  // 2. Test passenger
  Passenger p1(100, TicketType::SKI, DinString("1111"), DinString("Ivan"));
  std::cout << p1 << std::endl;

  // 3. Test child passenger
  ChildPassenger c1(101, TicketType::SKI, DinString("2222"), DinString("Marko"),
                    DinString("1111"));
  std::cout << c1 << std::endl;

  // 4. Create SkiLift (ski season, 2 seats per round, 5 minutes per ride)
  SkiLift<TicketType::SKI, 2, 5> lift;
  lift.open();

  // 5. Add Passengers
  lift.addPassenger(&p1);
  lift.addPassenger(&c1);

  std::cout << "Lift after adding passengers:\n";
  std::cout << lift << std::endl;

  // 6. Transport one round
  lift.transportRound();
  std::cout << "Lift after transporting one round:\n";
  std::cout << lift << std::endl;

  // 7. Add some more passengers to show partial seat fill
  Passenger p2(102, TicketType::SKI, DinString("3333"), DinString("Milos"));
  Passenger p3(103, TicketType::SKI, DinString("4444"), DinString("Ana"));

  lift.addPassenger(&p2);
  lift.addPassenger(&p3);

  std::cout << "Lift after adding Milos and Ana:\n";
  std::cout << lift << std::endl;

  // Transport again (2 seats → both get transported)
  lift.transportRound();
  std::cout << "Lift after second transport round:\n";
  std::cout << lift << std::endl;

  // 8. Try to add a SUMMER ticket during ski season → should fail
  Passenger summerGuy(104, TicketType::SUMMER, DinString("5555"),
                      DinString("Petar"));
  if (!lift.addPassenger(&summerGuy)) {
    std::cout << "Petar CANNOT enter lift (wrong season ticket)." << std::endl;
  }

  return 0;
}