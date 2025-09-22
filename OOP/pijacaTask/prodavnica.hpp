#pragma once
#include "list.hpp"
#include "proizvod.hpp"

class Prodavnica {
private:
  DinString naziv;
  List<Proizvod *> proizvodi;

public:
  Prodavnica(const DinString &naziv) : naziv(naziv) {}

  DinString getNaziv() const { return naziv; }

  bool dodajProizvod(Proizvod *p) {
    for (int i = 1; i <= proizvodi.size(); i++) {
      Proizvod *existing;

      proizvodi.read(i, existing);
      if (existing->getNaziv() == p->getNaziv()) {
        return false;
      }
    }

    proizvodi.add(proizvodi.size() + 1, p);
    return true;
  }

  bool obrisiProizvod(const DinString &naziv) {
    for (int i = 1; i <= proizvodi.size(); i++) {
      Proizvod *p;

      proizvodi.read(i, p);
      if (p->getNaziv() == naziv) {
        proizvodi.remove(i);
        return true;
      }
    }

    return false;
  }

  bool obrisiProizvod(int index) {
    if (index < 1 || index > static_cast<int>(proizvodi.size())) {
      return false;
    }

    proizvodi.remove(index);
    return true;
  }

  void akcija() {
    for (int i = 1; i <= proizvodi.size(); i++) {
      Proizvod *p;

      proizvodi.read(i, p);
      p->izracunajPopust();
    }
  }

  double getProsecnaCena() const {
    double sum{};

    for (int i = 1; i <= proizvodi.size(); i++) {
      Proizvod *p;

      proizvodi.read(i, p);
      sum += static_cast<double>(p->getCena());
    }

    double avg = sum / static_cast<double>(proizvodi.size());
    return avg;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const Prodavnica &prodavnica) {
    os << "Naziv prodavnice:" << prodavnica.naziv << "\n";

    for (int i = 1; i <= prodavnica.proizvodi.size(); i++) {
      Proizvod *p;

      prodavnica.proizvodi.read(i, p);
      p->ispis();

      os << "\n";
    }

    return os;
  }
};