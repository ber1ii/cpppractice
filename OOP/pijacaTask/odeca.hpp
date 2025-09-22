#pragma once
#include "proizvod.hpp"

enum class Velicina { XS, S, M, L, XL };
enum class Tip { MAJICA, PANTALONE };

inline DinString getVelicina(Velicina velicina) {
  switch (velicina) {
  case Velicina::XS:
    return DinString("XS");
  case Velicina::S:
    return DinString("S");
  case Velicina::M:
    return DinString("M");
  case Velicina::L:
    return DinString("L");
  case Velicina::XL:
    return DinString("XL");
  }

  return DinString("UNKNOWN");
}

inline DinString getTip(Tip tip) {
  if (tip == Tip::MAJICA) {
    return DinString("MAJICA");
  } else {
    return DinString("PANTALONE");
  }
}

class Odeca : public Proizvod {
private:
  Velicina velicina;
  Tip tip;
  static int countLandXL;

public:
  Odeca(int cena, const DinString &naziv, Velicina velicina, Tip tip)
      : Proizvod(cena, naziv), velicina(velicina), tip(tip) {
    if (velicina == Velicina::L || velicina == Velicina::XL) {
      countLandXL++;
    }
  }

  int getCountLandXL() const { return countLandXL; }

  void izracunajPopust() override {
    if (velicina == Velicina::XS && tip == Tip::MAJICA) {
      cena = cena - (cena * 0.6);
    } else if (tip == Tip::MAJICA) {
      cena = cena - (cena * 0.5);
    } else if (tip == Tip::PANTALONE) {
      cena = cena - (cena * 0.33);
    }
  }

  void ispis() const override {
    Proizvod::ispis();
    std::cout << ", Velicina: " << getVelicina(velicina)
              << ", Tip: " << getTip(tip);
  }
};