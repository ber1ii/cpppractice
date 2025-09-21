#pragma once
#include "planeta.hpp"
#include <cstdio>

class Satelit : public Planeta {
private:
  static int brojStenovitih;

public:
  Satelit() : Planeta("", Tip::GASOVITA, 0, false) {}
  Satelit(const DinString &naziv, Tip tip, double masa, bool naseljiva)
      : Planeta(naziv, tip, masa, naseljiva) {
    if (tip == Tip::STENOVITA) {
      brojStenovitih++;
    }
  }

  ~Satelit() {
    if (tip == Tip::STENOVITA) {
      brojStenovitih--;
    }
  }

  void ispisi() const override {
    std::cout << "naziv: " << naziv << "\n";
    std::cout << "tip: " << tipToString(tip) << "\n";

    char buffer[50];
    sprintf(buffer, "%.2e kg", masa);
    std::cout << "masa: " << buffer << "\n";

    std::cout << "naseljiva: " << (naseljiva ? "da" : "ne") << "\n";
    std::cout << "broj stenovitih: " << brojStenovitih << "\n";
  }
};