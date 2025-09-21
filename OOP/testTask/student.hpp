#pragma once
#include "predmet.hpp"

class Student {
private:
  Predmet p1;
  Predmet p2;

public:
  Student(const Predmet &p1, const Predmet &p2) : p1(p1), p2(p2) {}

  DinString comparePredmeti() {
    if (p1.getUkupniPoeni() < p2.getUkupniPoeni()) {
      return p2.getNaziv();
    } else if (p2.getUkupniPoeni() < p1.getUkupniPoeni()) {
      return p1.getNaziv();
    } else {
      return DinString("Ima jednako poena iz oba predmeta");
    }
  }

  void ispis() {
    std::cout << "===== Predmet 1 =====\n";
    p1.ispis();
    std::cout << "===== Predmet 2 =====\n";
    p2.ispis();

    std::cout << "\nPredmet iz kog je student osvojio vise bodova: "
              << comparePredmeti() << "\n";
  }
};