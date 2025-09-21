#pragma once
#include "lek.hpp"
#include "list.hpp"

class EvidencijaLekova {
private:
  DinString nazivApoteke;
  DinString datum;
  List<Lek> lekovi;

public:
  EvidencijaLekova() : nazivApoteke(""), datum("") {}
  EvidencijaLekova(DinString nazivApoteke, DinString datum)
      : nazivApoteke(nazivApoteke), datum(datum) {}

  bool dodajLekParameter(long jkl, DinString naziv, double jedinicnaCena,
                         int kolicina) {
    for (int i = 1; i <= lekovi.size(); i++) {
      Lek l;

      lekovi.read(i, l);
      if (l.getNaziv() == naziv) {
        return false;
      }
    }

    lekovi.add(lekovi.size() + 1, Lek(jkl, naziv, jedinicnaCena, kolicina));
    return true;
  }

  bool dodajLek(Lek l) {
    for (int i = 1; i <= lekovi.size(); i++) {
      Lek lekCopy;

      lekovi.read(i, lekCopy);
      if (l.getNaziv() == lekCopy.getNaziv()) {
        return false;
      }
    }

    lekovi.add(1, l);
    return true;
  }

  void brisanjeLeka(int i) { lekovi.remove(i); }

  void sortLekovi() {
    for (int i = 1; i <= lekovi.size(); i++) {
      for (int j = 1; j <= lekovi.size() - i; j++) {
        Lek a, b;

        lekovi.read(j, a);
        lekovi.read(j + 1, b);

        if (a.calculateCost() < b.calculateCost()) {
          lekovi.remove(j);
          lekovi.add(j, b);
          lekovi.remove(j + 1);
          lekovi.add(j + 1, a);
        }
      }
    }
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const EvidencijaLekova &lekovi) {
    os << lekovi.nazivApoteke << ":" << "\n";

    for (int i = 1; i <= lekovi.lekovi.size(); i++) {
      Lek l;

      lekovi.lekovi.read(i, l);
      os << l;
    }

    os << "\n-----------------";
    return os;
  }
};