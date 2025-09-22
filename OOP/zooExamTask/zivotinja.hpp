#ifndef ZIVOTINJA_HPP_INCLUDED
#define ZIVOTINJA_HPP_INCLUDED

#include "dinstring.hpp"

class Zivotinja {
protected:
  DinString naziv;
  int godine;
  double tezina;

public:
  Zivotinja(const DinString &naziv, int godine, double tezina)
      : naziv(naziv), godine(godine), tezina(tezina) {}

  DinString getNaziv() const { return naziv; }
  int getGodine() const { return godine; }
  double getTezine() const { return tezina; }

  void setTezina(double newTezina) {
    if (newTezina > 0) {
      tezina = newTezina;
    }
  }

  virtual void ispisi() const = 0;
};

#endif
