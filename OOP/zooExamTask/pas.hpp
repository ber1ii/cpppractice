#ifndef PAS_HPP_INCLUDED
#define PAS_HPP_INCLUDED

#include "zivotinja.hpp"
#include <cstdio>

class Pas : public Zivotinja {
private:
  static int brojPasa;

public:
  Pas(const DinString &naziv, int godine, double tezina)
      : Zivotinja(naziv, godine, tezina) {
    brojPasa++;
  }

  ~Pas() { brojPasa--; }

  void ispisi() const override {
    std::cout << "\nnaziv: " << naziv;
    std::cout << "\ngodine: " << godine;

    char buffer[50];
    sprintf(buffer, "%.2f kg", tezina);
    std::cout << "\ntezina: " << buffer;
    std::cout << "\ntrenutno pasa: " << brojPasa;
  }
};

#endif