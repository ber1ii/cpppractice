#pragma once
#include "planeta.hpp"
#include <cstdio>
#include <iostream>

class Satelit : public Planeta {
private:
  static int brojStenovitih;

public:
  Satelit(const DinString &naziv, Tip tip, double masa, bool naseljiva)
      : Planeta(naziv, tip, masa, naseljiva) {
    brojStenovitih++;
  }

  Satelit() : Planeta(DinString(""), Tip::GASOVITA, 0.0, false) {}

  ~Satelit() { brojStenovitih--; }

  void ispisi() override {
    std::cout << "naziv: " << naziv;
    std::cout << "\ntip: " << tipToString(tip);

    char buffer[50];
    sprintf(buffer, "%.2e kg", masa);
    std::cout << "\nmasa: " << buffer;
    std::cout << "\nbroj stenovitih: " << brojStenovitih;
  }
};