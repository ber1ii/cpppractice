#ifndef PLANETA_HPP_INCLUDED
#define PLANETA_HPP_INCLUDED

#include "dinstring.hpp"

enum class Tip { STENOVITA, GASOVITA, LEDENA };

inline DinString tipToString(Tip tip) {
  switch (tip) {
  case Tip::STENOVITA:
    return DinString("STENOVITA");
  case Tip::GASOVITA:
    return DinString("GASOVITA");
  case Tip::LEDENA:
    return DinString("LEDENA");
  }
  return DinString("UNKNOWN");
}

class Planeta {
protected:
  DinString naziv;
  Tip tip;
  double masa;
  bool naseljiva;

public:
  Planeta()
      : naziv(DinString("")), tip(Tip::GASOVITA), masa(0), naseljiva(false) {}

  Planeta(const DinString &naziv, Tip tip, double masa, bool naseljiva)
      : naziv(naziv), tip(tip), masa(masa), naseljiva(naseljiva) {}

  ~Planeta() {}

  DinString getNaziv() const { return naziv; }
  Tip getTip() const { return tip; }
  double getMasa() const { return masa; }
  bool getNaseljivost() const { return naseljiva; }

  void setNaseljivost(bool naseljivost) {
    if (naseljiva != naseljivost) {
      naseljiva = naseljivost;
    }
  }

  virtual void ispisi() = 0;
};

#endif