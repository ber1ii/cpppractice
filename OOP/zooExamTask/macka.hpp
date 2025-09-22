#ifndef MACKA_HPP_INCLUDED
#define MACKA_HPP_INCLUDED

#include "zivotinja.hpp"
#include <cstdio>

class Macka : public Zivotinja {
private:
  DinString boja;

public:
  Macka(const DinString &naziv, int godine, double tezina,
        const DinString &boja)
      : Zivotinja(naziv, godine, tezina), boja(boja) {}

  void ispisi() const override {
    std::cout << "\nnaziv: " << naziv;
    std::cout << "\ngodine: " << godine;

    char buffer[50];
    sprintf(buffer, "%.2f kg", tezina);
    std::cout << "\ntezina: " << buffer;

    std::cout << "\nboja: " << boja;
  }
};

#endif