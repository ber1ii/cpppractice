#pragma once
#include "list.hpp"
#include "test.hpp"

class Predmet {
private:
  DinString naziv;
  List<Test *> testovi;

public:
  Predmet() : naziv("") {}
  Predmet(const DinString &naziv) : naziv(naziv) {}
  Predmet(const Predmet &predmet)
      : naziv(predmet.naziv), testovi(predmet.testovi) {}

  void dodajTest(Test &t) { testovi.add(testovi.size() + 1, &t); }

  bool polozio() {
    int ukupnoBodova{};
    int countPolozeniTestovi{};

    for (int i = 1; i <= testovi.size(); i++) {
      Test *t;

      testovi.read(i, t);
      ukupnoBodova += t->getPoeni();

      if (t->polozio()) {
        countPolozeniTestovi++;
      }
    }

    if (countPolozeniTestovi == testovi.size() && ukupnoBodova > 55) {
      return true;
    }
    return false;
  }

  int getUkupniPoeni() {
    int ukupniPoeni{};

    if (testovi.empty()) {
      return 0;
    }

    for (int i = 1; i <= testovi.size(); i++) {
      Test *t;

      testovi.read(i, t);
      ukupniPoeni += t->getPoeni();
    }

    return ukupniPoeni;
  }

  DinString getNaziv() const { return naziv; }

  void ispis() {
    std::cout << "Naziv predmeta: " << naziv << "\n";

    for (int i = 1; i <= testovi.size(); i++) {
      Test *t;

      testovi.read(i, t);
      t->ispis();
      std::cout << "\n";
    }
  }
};