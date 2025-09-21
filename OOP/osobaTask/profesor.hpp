#pragma once
#include "osoba.hpp"

class Profesor : public Osoba {
private:
  DinString nazivPredmeta;

public:
  Profesor() : Osoba(), nazivPredmeta(DinString("")) {}
  Profesor(const DinString &ime, const DinString &prezime,
           const DinString &nazivPredmeta)
      : Osoba(ime, prezime), nazivPredmeta(nazivPredmeta) {}
  Profesor(const Profesor &profesor)
      : Osoba(profesor.ime, profesor.prezime),
        nazivPredmeta(profesor.nazivPredmeta) {}

  void ispis() const override {
    Osoba::ispis();
    std::cout << " Naziv predmeta: " << nazivPredmeta;
  }
};