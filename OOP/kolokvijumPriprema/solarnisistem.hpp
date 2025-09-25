#pragma once
#include "list.hpp"
#include "satelit.hpp"

class SolarniSistem {
private:
  int kapacitet;
  List<Satelit> planete;

public:
  SolarniSistem() : kapacitet(0) {}

  SolarniSistem(int kapacitet) : kapacitet(kapacitet) {}

  int getKapacitet() const { return kapacitet; }
  List<Satelit> getPlanete() const { return planete; }

  bool dodaj(Satelit s) {
    if (planete.size() < kapacitet) {
      planete.add(planete.size() + 1, s);
      return true;
    } else {
      std::cout << "Neuspesno dodavanje: premasen kapacitet!";
      return false;
    }
  }

  int izbaci(const DinString &naziv) {
    for (int i = 1; i <= planete.size(); i++) {
      Satelit existing;

      planete.read(i, existing);
      if (existing.getNaziv() == naziv) {
        std::cout << "Uspesno izbacivanje elementa sa nazivom" << naziv;
        planete.remove(i);

        return i;
      }
    }

    return -1;
  }

  int tezeOdProseka() {
    double sum{};
    int count{};

    if (planete.size() == 0) {
      return 0;
    }

    for (int i = 1; i <= planete.size(); i++) {
      Satelit trenutni;

      planete.read(i, trenutni);
      sum += trenutni.getMasa();
    }

    double avg = sum / static_cast<double>(planete.size());

    for (int i = 1; i <= planete.size(); i++) {
      Satelit check;

      planete.read(i, check);
      if (check.getMasa() > avg) {
        count++;
      }
    }

    return count;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const SolarniSistem &solar) {
    os << "U solarnom sistemu se trenutno nalazi: ";

    int count{};

    for (int i = 1; i <= solar.planete.size(); i++) {
      Satelit s;

      solar.planete.read(i, s);
      if (s.getNaseljivost()) {
        count++;
      }
    }

    os << count << " naseljivih planeta";
    return os;
  }
};