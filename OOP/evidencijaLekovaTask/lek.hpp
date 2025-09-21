#pragma once
#include "artikal.hpp"
#include "dinstring.hpp"

class Lek : public Artikal {
private:
  long jkl;
  DinString naziv;
  double jedinicnaCena;
  int kolicina;

public:
  Lek() : jkl(0), naziv(DinString("")), jedinicnaCena(0), kolicina(0) {}
  Lek(long jkl, const char *naziv, double jedinicnaCena, int kolicina)
      : jkl(jkl), naziv(naziv), jedinicnaCena(jedinicnaCena),
        kolicina(kolicina) {}
  Lek(long jkl, const DinString &naziv, double jedinicnaCena, int kolicina)
      : jkl(jkl), naziv(naziv), jedinicnaCena(jedinicnaCena),
        kolicina(kolicina) {}
  Lek(const Lek &lek)
      : jkl(lek.jkl), naziv(lek.naziv), jedinicnaCena(lek.jedinicnaCena),
        kolicina(lek.kolicina) {}

  DinString getNaziv() const { return naziv; }
  long getJKL() const { return jkl; }
  double getJedCena() const { return jedinicnaCena; }
  int getKolicina() const { return kolicina; }

  double calculateCost() const override {
    double value{};

    value = kolicina * jedinicnaCena;
    return value;
  }

  friend std::ostream &operator<<(std::ostream &os, const Lek &lek) {
    os << "JKL leka: " << lek.jkl << "\nNaziv leka: " << lek.naziv
       << "\nVrednost leka: " << lek.calculateCost();

    return os;
  }
};