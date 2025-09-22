#include "macka.hpp"
#include "pas.hpp"
#include "zooloskiVrt.hpp"

int main() {
  Pas *p1 = new Pas(DinString("Leo"), 5, 8.3);
  Pas *p2 = new Pas(DinString("Deni"), 10, 20.75);
  Pas *p3 = new Pas(DinString("Dik"), 8, 12.6);

  Macka *m1 = new Macka(DinString("Ena"), 12, 8.6, DinString("bela"));
  Macka *m2 = new Macka(DinString("Mica Ubica"), 9, 6.2, DinString("sarena"));
  Macka *m3 = new Macka(DinString("Negro"), 4, 5.6, DinString("crna"));

  std::cout << "Ispisujemo pse:" << std::endl;
  p1->ispisi();
  p2->ispisi();
  p3->ispisi();

  std::cout << "\nIspisujemo macke:" << std::endl;
  m1->ispisi();
  m2->ispisi();
  m3->ispisi();

  ZooloskiVrt *zoo = new ZooloskiVrt("Palic", 5);
  std::cout << "\nZoo vrt pre dodavanja:" << std::endl;
  std::cout << *zoo;

  zoo->dodajZivotinje(p3);
  zoo->dodajZivotinje(p2);
  zoo->dodajZivotinje(m1);
  zoo->dodajZivotinje(m2);
  zoo->dodajZivotinje(m3);

  std::cout << "Dodajemo 6. zivotinju u zoo kapaciteta 5 (ocekivano false) = "
            << (zoo->dodajZivotinje(p1) ? "true" : "false") << std::endl;

  std::cout << *zoo;

  std::cout << "\nIzbacujemo zivotinju m2 (Mica Ubica)";
  zoo->izbaci("Mica Ubica");

  std::cout << "\n" << *zoo;

  std::cout << "U zoo vrtu ima: " << zoo->prosecnoStarijiOd(6)
            << " zivotinja starijih od proseka" << std::endl;

  return 0;
}