#include "solarniSistem.hpp"
#include <iostream>

int main() {
  Satelit earth("Zemlja", Tip::STENOVITA, 5.97e24, true);
  Satelit mars("Mars", Tip::STENOVITA, 6.39e23, false);
  Satelit jupiter("Jupiter", Tip::GASOVITA, 1.90e27, false);
  Satelit pluto("Pluton", Tip::LEDENA, 1.31e22, false);

  std::cout << "=== Ispisi pojedinacne planete ===\n";
  earth.ispisi();
  std::cout << "\n";

  mars.ispisi();
  std::cout << "\n";

  jupiter.ispisi();
  std::cout << "\n";

  SolarniSistem ss(3);

  std::cout << "=== Test dodavanja ===\n";
  std::cout << "Dodaj Zemlja: " << (ss.dodaj(earth) ? "uspesno" : "neuspesno")
            << "\n";
  std::cout << "Dodaj Mars: " << (ss.dodaj(mars) ? "uspesno" : "neuspesno")
            << "\n";
  std::cout << "Dodaj Jupiter: "
            << (ss.dodaj(jupiter) ? "uspesno" : "neuspesno") << "\n";
  // Try adding beyond capacity
  std::cout << "Dodaj Pluton: " << (ss.dodaj(pluto) ? "uspesno" : "neuspesno")
            << "\n";

  std::cout << "\n";

  std::cout << ss;

  // Test remove
  std::cout << "\n=== Test izbacivanja ===\n";
  int index = ss.izbaci("Mars");
  if (index != -1) {
    std::cout << "Uspesno izbacen Mars sa indeksom " << index << "\n";
  } else {
    std::cout << "Planet Mars nije nadjen\n";
  }

  // Print again
  std::cout << ss;

  // Test teze od proseka
  std::cout << "\n=== Test tezeOdProseka ===\n";
  int cnt = ss.tezeOdProseka();
  std::cout << "Broj planeta tezih od proseka: " << cnt << "\n";

  return 0;
}