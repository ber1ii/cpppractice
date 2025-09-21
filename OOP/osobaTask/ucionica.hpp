#pragma once
#include "list.hpp"
#include "osoba.hpp"

class Ucionica {
private:
  List<Osoba *> ucionica;
  DinString naziv;
  int kapacitet;

public:
  Ucionica(const DinString &naziv, int kapacitet)
      : naziv(naziv), kapacitet(kapacitet) {}

  bool dodajOsobu(Osoba *s) {
    if (ucionica.size() < kapacitet) {
      ucionica.add(ucionica.size() + 1, s);
      return true;
    }

    return false;
  }

  void ispis() const {
    std::cout << "Naziv ucionice: " << naziv << "\n";

    if (!ucionica.empty()) {
      for (int i = 1; i <= ucionica.size(); i++) {
        Osoba *s;

        ucionica.read(i, s);
        s->ispis();
        std::cout << "\n";
      }
    } else {
      std::cout << "Nema prisutnih u ucionici.\n";
    }
  }

  ~Ucionica() {
    while (!ucionica.empty()) {
      Osoba *s;
      ucionica.read(1, s);
      delete s;
      ucionica.remove(1);
    }
  }
};