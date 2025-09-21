#pragma once
#include "dinstring.hpp"

class Test {
protected:
  DinString naziv;
  int osvojeniPoeni;

public:
  Test() : naziv(DinString("")), osvojeniPoeni(0) {}
  Test(const DinString &naziv, int osvojeniPoeni)
      : naziv(naziv), osvojeniPoeni(osvojeniPoeni) {}

  virtual int getPoeni() const = 0;
  virtual bool polozio() const = 0;

  void ispis() const {
    std::cout << "Naziv: " << naziv << "\n";
    std::cout << "Broj osvojenih poena: " << osvojeniPoeni << "\n";
  }
};