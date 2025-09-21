#pragma once
#include "dinstring.hpp"

class Osoba {
protected:
  DinString ime;
  DinString prezime;

public:
  Osoba() : ime(""), prezime("") {}
  Osoba(const DinString &ime, const DinString &prezime)
      : ime(ime), prezime(prezime) {}
  Osoba(const Osoba &osoba) : ime(osoba.ime), prezime(osoba.prezime) {}

  virtual void ispis() const {
    std::cout << "Ime: " << ime << ", Prezime: " << prezime;
  }
};