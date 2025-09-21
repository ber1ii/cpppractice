#pragma once
#include "dinstring.hpp"

enum class Tip { STENOVITA, GASOVITA, LEDENA };

inline DinString tipToString(Tip tip) {
  switch (tip) {
  case Tip::STENOVITA:
    return DinString("stenovita");
  case Tip::GASOVITA:
    return DinString("gasovita");
  case Tip::LEDENA:
    return DinString("ledena");
  }

  return DinString("nepoznat");
}

class Planeta {
protected:
  DinString naziv;
  Tip tip;
  double masa;
  bool naseljiva;

public:
  Planeta(const DinString &n, Tip t, double m, bool nas)
      : naziv(n), tip(t), masa(m), naseljiva(nas) {}

  virtual ~Planeta() {}
  DinString getNaziv() const { return naziv; }
  Tip getTip() const { return tip; }
  double getMasa() const { return masa; }
  bool getNaseljivost() const { return naseljiva; }

  void setNaseljivost(bool n) {
    if (naseljiva != n) {
      naseljiva = n;
    }
  }

  virtual void ispisi() const = 0;
};