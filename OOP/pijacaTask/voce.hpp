#pragma once
#include "proizvod.hpp"

class Voce : public Proizvod {
private:
  DinString zemljaPorekla;
  int rokTrajanja;

public:
  Voce(int cena, const DinString &naziv, const DinString &zemljaPorekla,
       int rokTrajanja)
      : Proizvod(cena, naziv), zemljaPorekla(zemljaPorekla),
        rokTrajanja(rokTrajanja) {}

  void izracunajPopust() override {
    if (rokTrajanja > 5) {
      cena = cena - (cena * 0.33);
    } else if (rokTrajanja >= 1 && rokTrajanja <= 5) {
      cena = cena - (cena * 0.66);
    } else {
      cena = 0;
    }
  }

  void ispis() const override {
    Proizvod::ispis();
    std::cout << ", zemlja porekla: " << zemljaPorekla
              << ", rok trajanja: " << rokTrajanja;
  }
};