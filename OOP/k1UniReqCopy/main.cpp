#include "game.hpp"
#include "player.hpp"
#include <iostream>

int main() {
  std::cout << "=== Testing Player ===" << std::endl;

  Player p1;       // Default constructor
  Player p2(5, 2); // Param constructor
  Player p3(p2);   // Copy constructor

  p1.addPoints(3); // add points
  p1.playGame();   // play one match
  p1.print();

  p1.reset(); // reset to zero
  p1.print();

  std::cout << "Points via getter: " << p2.getPoints()
            << ", Games via getter: " << p2.getGameNumber() << std::endl;

  p2.setPoints(8); // setter
  p2.print();

  std::cout << "\n=== Testing Game ===" << std::endl;

  Game g1;                       // default constructor
  Game g2(4, 2, GameState::PVE); // param constructor
  printGame(g1);
  printGame(g2);

  // log in
  g1.loginPlayer();
  printGame(g1);

  // play vs AI
  if (g1.startGamePVE()) {
    g1.win(); // win (+1)
  }
  printGame(g1);

  // play vs online
  if (g1.startGamePVP()) {
    g1.win();        // win (+2)
    g1.applyBonus(); // try bonus if >5 points
  }
  printGame(g1);

  // force points > 5 to trigger bonus
  Game g3(6, 1, GameState::PVP);
  printGame(g3);
  g3.applyBonus();
  printGame(g3);

  // simulate lose
  g1.lose();
  printGame(g1);

  // log out
  g1.logoutPlayer();
  printGame(g1);

  return 0;
}