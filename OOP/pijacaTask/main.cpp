#include "grad.hpp"
#include "odeca.hpp"
#include "voce.hpp"
#include <iostream>

int main() {
  // === Kreiraj proizvode ===
  Voce *jabuke =
      new Voce(100, "Jabuke", DinString("Srbija"), 10); // >5 dana -> 33% off
  Voce *banane =
      new Voce(120, "Banane", DinString("Ekvador"), 3); // 1–5 dana -> 66% off
  Voce *jagode =
      new Voce(200, "Jagode", DinString("Spanija"), 0); // 0 dana -> free
  Odeca *majicaXS =
      new Odeca(1000, "MajicaXS", Velicina::XS, Tip::MAJICA); // XS majica 60%
  Odeca *majicaL =
      new Odeca(2000, "MajicaL", Velicina::L, Tip::MAJICA); // L majica 50%
  Odeca *pantalone = new Odeca(3000, "Pantalone", Velicina::M,
                               Tip::PANTALONE); // Pantalone 33%

  // === Kreiraj prodavnice ===
  Prodavnica *p1 = new Prodavnica(DinString("Maxi"));
  Prodavnica *p2 = new Prodavnica(DinString("Univerexport"));

  // Dodavanje proizvoda (test duplikata ne dozvoljava isti naziv)
  p1->dodajProizvod(jabuke);
  p1->dodajProizvod(banane);
  p1->dodajProizvod(majicaXS);

  p2->dodajProizvod(jagode);
  p2->dodajProizvod(majicaL);
  p2->dodajProizvod(pantalone);

  std::cout << "=== Pre akcije ===" << std::endl;
  std::cout << *p1 << std::endl;
  std::cout << *p2 << std::endl;

  // Akcija - primeni popuste
  p1->akcija();
  p2->akcija();

  std::cout << "\n=== Posle akcije ===" << std::endl;
  std::cout << *p1 << std::endl;
  std::cout << *p2 << std::endl;

  // === Kreiraj grad i dodaj prodavnice ===
  Grad g(DinString("Novi Sad"));
  g.dodajProdavnicu(p1);
  g.dodajProdavnicu(p2);

  std::cout << "\n=== Najjeftinija prodavnica u gradu ===" << std::endl;
  g.ispisiNajjeftinijuProdavnicu();

  // Clean up (since we used new)
  delete jabuke;
  delete banane;
  delete jagode;
  delete majicaXS;
  delete majicaL;
  delete pantalone;
  delete p1;
  delete p2;

  return 0;
}