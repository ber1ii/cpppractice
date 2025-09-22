#pragma once
#include "prodavnica.hpp"

class Grad {
private:
  DinString naziv;
  List<Prodavnica *> prodavnice;

public:
  Grad() : naziv(DinString("")) {}
  Grad(const DinString &naziv) : naziv(naziv) {}

  bool dodajProdavnicu(Prodavnica *p) {
    for (int i = 1; i <= prodavnice.size(); i++) {
      Prodavnica *existing;

      prodavnice.read(i, existing);
      if (existing->getNaziv() == p->getNaziv()) {
        return false;
      }
    }

    prodavnice.add(prodavnice.size() + 1, p);
    return true;
  }

  void ispisiNajjeftinijuProdavnicu() {
    if (prodavnice.empty()) {
      std::cout << "Nema prodavnica u listi!\n";
      return;
    }

    Prodavnica *pNajbolja;
    prodavnice.read(1, pNajbolja);
    double minAvg = pNajbolja->getProsecnaCena();

    for (int i = 2; i <= prodavnice.size(); i++) {
      Prodavnica *pCurrent;
      prodavnice.read(i, pCurrent);
      double currentAvg = pCurrent->getProsecnaCena();

      if (currentAvg < minAvg) {
        minAvg = currentAvg;
        pNajbolja = pCurrent;
      }
    }

    std::cout << "Najjeftinija prodavnica je: \n";
    std::cout << *pNajbolja << "\n";
  }
};