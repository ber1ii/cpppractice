#pragma once
#include "list.hpp"
#include "satelit.hpp"

class SolarniSistem {
private:
  int kapacitet;
  List<Satelit> planete;

public:
  SolarniSistem() : kapacitet(10) {}
  SolarniSistem(int kapacitet) : kapacitet(kapacitet) {}

  int getKapacitet() const { return kapacitet; }
  List<Satelit> getPlanete() const { return planete; }

  bool dodaj(Satelit s) {
    if (planete.size() < kapacitet) {
      planete.add(planete.size() + 1, s);
    } else {
      std::cout << "Neuspesno dodavanje: premasen kapacitet!\n";
      return false;
    }

    return true;
  }

  int izbaci(const DinString &naziv) {
    for (int i = 1; i <= planete.size(); i++) {
      Satelit s;

      planete.read(i, s);
      if (naziv == s.getNaziv()) {
        planete.remove(i);
        std::cout << "Uspesno izbacivanje elementa sa nazivom " << naziv
                  << "\n";
        return i;
      }
    }
    return -1;
  }

  int tezeOdProseka() {
    int countTeze{};
    double prosek{};
    double ukupnaMasa{};

    if (planete.size() == 0) {
      return 0;
    }

    for (int i = 1; i <= planete.size(); i++) {
      Satelit s;

      planete.read(i, s);
      ukupnaMasa += s.getMasa();
    }

    prosek = ukupnaMasa / static_cast<double>(planete.size());

    for (int i = 1; i <= planete.size(); i++) {
      Satelit s;

      planete.read(i, s);
      if (s.getMasa() > prosek) {
        countTeze++;
      }
    }

    return countTeze;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const SolarniSistem &sistem) {
    os << "U solarnom sistemu se trenutno nalazi ";

    int countNaseljive{};
    for (int i = 1; i <= sistem.planete.size(); i++) {
      Satelit s;

      sistem.planete.read(i, s);
      if (s.getNaseljivost()) {
        countNaseljive++;
      }
    }

    os << countNaseljive;
    os << " naseljivih planeta.\n";

    return os;
  }
};