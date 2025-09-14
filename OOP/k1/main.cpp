#include "game.hpp"
#include <cstdlib>
#include <iostream>

void showMenu();

int main() {
  Game g;
  char keystroke;
  size_t n{};

  std::cout << "Press Enter to log in...";
  keystroke = std::cin.get();

  if (keystroke == '\n') {
    std::cout << "Logging player in..." << std::endl;
    g.loginPlayer();
    printGame(g);

    while (true) {
      std::cout << "\nChoose an option:" << std::endl;
      showMenu();
      std::cin >> n;
      std::cin.ignore();

      switch (n) {
      case 1: {
        if (g.startGamePVE()) {
          if (std::rand() % 2 == 0) {
            std::cout << "You won vs AI! +1" << std::endl;
            g.win();
          } else {
            std::cout << "You lost vs AI! -1" << std::endl;
            g.lose();
          }
        }
      } break;
      case 2: {
        if (g.startGamePVP()) {
          if (std::rand() % 2 == 0) {
            std::cout << "You won vs an opponent! +2" << std::endl;
            g.win();
            g.applyBonus();
          } else {
            std::cout << "You lost vs an opponent! -2" << std::endl;
            g.lose();
          }
        }
      } break;
      case 3: {
        printGame(g);
      } break;
      case 4: {
        std::cout << "Logging out..." << std::endl;
        g.logoutPlayer();
        return 0;
      } break;
      default:
        std::cout << "Invalid choice, try again." << std::endl;
      }
    }
  }
  return 0;
}

void showMenu() {
  std::cout << "1. Practice vs AI" << std::endl;
  std::cout << "2. Play Online" << std::endl;
  std::cout << "3. View score" << std::endl;
  std::cout << "4. Exit" << std::endl;
}