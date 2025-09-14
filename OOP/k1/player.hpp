#pragma once
#include <iostream>

class Player {
private:
    int points;
    int gameNumber;
    
public:
    // Default constructor
    Player(int p = 0, int g = 0)
        : points(p), gameNumber(g) {}

    // Copy constructor
    Player(const Player& p)
        : points(p.points), gameNumber(p.gameNumber) {}

    // Getters
    int getPoints() const { return points; }
    int getGameNumber() const { return gameNumber; }

    // Setter for points
    void setPoints(int p) { points = p; }

    void addPoints(int x) { points += x; }
    void playGame() { gameNumber++; }
    void reset() {
        gameNumber = 0;
        points = 0;
    }
    void print() const {
        std::cout << "Player info\nPoints: " << points << "\nGames played: " << gameNumber << std::endl;
    }
};