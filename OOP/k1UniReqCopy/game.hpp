#pragma once
#include "player.hpp"
#include <cstdlib>
#include <iostream>

enum class GameState { UNKNOWN_PLAYER, PLAYER_PROFILE, PVE, PVP };

class Game {
private:
  Player p;
  GameState currentState;

  static constexpr int MAX_POINTS = 10;
  static constexpr int MAX_GAMES = 5;

public:
  // Default constructor
  Game() : p(0, 0), currentState(GameState::UNKNOWN_PLAYER) {}

  // Constructor with parameters
  Game(int points, int games, GameState state)
      : p(points, games), currentState(state) {}

  bool loginPlayer() {
    if (currentState == GameState::UNKNOWN_PLAYER) {
      currentState = GameState::PLAYER_PROFILE;
      return true;
    }
    return false;
  };
  bool logoutPlayer() {
    if (currentState != GameState::UNKNOWN_PLAYER) {
      p.reset();
      currentState = GameState::UNKNOWN_PLAYER;
      return true;
    }
    return false;
  };
  bool startGamePVE() {
    if (currentState == GameState::PLAYER_PROFILE &&
        p.getGameNumber() < MAX_GAMES) {
      p.playGame();
      currentState = GameState::PVE;
      return true;
    } else {
      std::cout << "Max number of games reached!" << std::endl << std::flush;
      return false;
    }
  };
  bool startGamePVP() {
    if (currentState == GameState::PLAYER_PROFILE &&
        p.getGameNumber() < MAX_GAMES) {
      p.playGame();
      currentState = GameState::PVP;
      return true;
    } else {
      std::cout << "Max number of games reached!" << std::endl << std::flush;
      return false;
    }
  };
  bool win() {
    int add{};

    if (currentState == GameState::PVE) {
      add = 1;
    } else if (currentState == GameState::PVP) {
      add = 2;
    }

    if (add > 0 && p.getPoints() < MAX_POINTS) {
      int newPoints = p.getPoints() + add;

      if (newPoints > MAX_POINTS) {
        newPoints = MAX_POINTS;
      }
      p.setPoints(newPoints);

      return true;
    }

    return false;
  };
  bool lose() {
    int sub{};

    if (currentState == GameState::PVE) {
      sub = 1;
    } else if (currentState == GameState::PVP) {
      sub = 2;
    }

    if (sub > 0 && p.getPoints() >= sub) {
      p.setPoints(p.getPoints() - sub);
      return true;
    }

    return false;
  };
  bool applyBonus() {
    if (currentState == GameState::PVP && p.getPoints() > 5) {
      int bonus = (rand() % 3) + 1;
      int newPoints = p.getPoints() + bonus;

      if (newPoints > MAX_POINTS) {
        newPoints = MAX_POINTS;
      }
      p.setPoints(newPoints);
      std::cout << "You got " << bonus << " points!" << std::endl;
      return true;
    }
    return false;
  };

  // Friend function for printing game info
  friend void printGame(const Game &g);
};

// Friend function outside the scope of class Game
inline void printGame(const Game &g) {
  std::cout << "=== GAME INFO ===" << std::endl;
  g.p.print();
  std::cout << "State: ";
  switch (g.currentState) {
  case GameState::UNKNOWN_PLAYER:
    std::cout << "UNKNOWN PLAYER";
    break;
  case GameState::PLAYER_PROFILE:
    std::cout << "PLAYER X";
    break;
  case GameState::PVE:
    std::cout << "PVE (vs AI)";
    break;
  case GameState::PVP:
    std::cout << "PVP (vs Human)";
    break;
  }
  std::cout << std::endl;
}