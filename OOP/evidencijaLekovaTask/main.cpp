#include "evidencijaLekova.hpp"

int main() {
  Lek l1(1, "Rivotril", 122.5, 1021);
  Lek l2(2, "Ksalol", 124.6549, 567);

  std::cout << "Vrednost leka Rivotril je: " << l1.calculateCost() << std::endl;

  EvidencijaLekova apoteka("Goodwill", "21.9.2025.");
  apoteka.dodajLek(l1);
  apoteka.dodajLek(l2);

  std::cout << apoteka;

  return 0;
}