#ifndef ZOOLOSKI_VRT_HPP_INCLUDED
#define ZOOLOSKI_VRT_HPP_INCLUDED

#include "list.hpp"
#include "macka.hpp"
#include "pas.hpp"
#include "zivotinja.hpp"

class ZooloskiVrt {
private:
  DinString naziv;
  int kapacitet;
  List<Zivotinja *> zivotinje;

public:
  ZooloskiVrt(const DinString &naziv, int kapacitet)
      : naziv(naziv), kapacitet(kapacitet) {}

  bool dodajZivotinje(Zivotinja *z) {
    if (zivotinje.size() < kapacitet) {
      for (int i = 1; i <= zivotinje.size(); i++) {
        Zivotinja *existing;

        zivotinje.read(i, existing);

        if (existing->getNaziv() == z->getNaziv()) {
          return false;
        }
      }

      zivotinje.add(zivotinje.size() + 1, z);
      return true;
    } else {
      return false;
    }
  }

  int izbaci(const DinString &naziv) {
    for (int i = 1; i <= zivotinje.size(); i++) {
      Zivotinja *z;

      zivotinje.read(i, z);
      if (z->getNaziv() == naziv) {
        zivotinje.remove(i);
        return i;
      }
    }

    return -1;
  }

  int prosecnoStarijiOd(int godine) {
    int sum{};

    for (int i = 1; i <= zivotinje.size(); i++) {
      Zivotinja *z;

      zivotinje.read(i, z);
      sum += z->getGodine();
    }

    double avg = static_cast<double>(sum) / zivotinje.size();
    int count{};

    for (int i = 1; i <= zivotinje.size(); i++) {
      Zivotinja *z;

      zivotinje.read(i, z);
      if (z->getGodine() > avg) {
        count++;
      }
    }

    return count;
  }

  friend std::ostream &operator<<(std::ostream &os, const ZooloskiVrt &zoo) {
    os << "U zoo vrtu " << zoo.naziv;

    int brojMacaka{};
    int brojPasa{};

    for (int i = 1; i <= zoo.zivotinje.size(); i++) {
      Zivotinja *z;

      zoo.zivotinje.read(i, z);
      if (dynamic_cast<Pas *>(z) != nullptr) {
        brojPasa++;
      } else if (dynamic_cast<Macka *>(z) != nullptr) {
        brojMacaka++;
      }
    }

    os << " ima " << brojPasa << " pas(a) i " << brojMacaka
       << " macka/macaka.\n";

    return os;
  }
};

#endif