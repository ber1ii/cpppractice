#pragma once
#include "dinstring.hpp"
#include <iostream>

class Proizvod {
protected:
  int cena;
  DinString naziv;

public:
  Proizvod(int cena, const DinString &naziv) : cena(cena), naziv(naziv) {}

  DinString getNaziv() const { return naziv; }
  int getCena() const { return cena; }

  virtual void izracunajPopust() = 0;

  virtual void ispis() const {
    std::cout << " Naziv proizvoda: " << naziv << ", cena proizvoda: " << cena;
  }
};