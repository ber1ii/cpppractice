#include "satelit.hpp"
#include "solarnisistem.hpp"

int main() {
  Satelit s = Satelit("Mars", Tip::STENOVITA, 5.97e24, false);
  Satelit s1 = Satelit("Zemlja", Tip::STENOVITA, 5.24e27, true);
  Satelit s2 = Satelit("Jupiter", Tip::GASOVITA, 8.25e20, false);

  std::cout << "Ispisujemo Mars: \n";
  s.ispisi();
  std::cout << "\n\nIspisujemo Zemlju: \n";
  s1.ispisi();
  std::cout << "\n\nIspisujemo Jupiter: \n";
  s2.ispisi();

  SolarniSistem sistem = SolarniSistem(3);

  std::cout << "\n\nIspisujemo prazan solarni sistem: \n" << sistem;

  sistem.dodaj(s);
  sistem.dodaj(s1);
  sistem.dodaj(s2);

  std::cout << "\n\nNakon dodavanja: " << sistem << "\n\n";

  sistem.dodaj(s);

  std::cout << "\n\nU sistemu ima " << sistem.tezeOdProseka()
            << " planeta tezih od proseka.\n";
}