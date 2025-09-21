#include <cstdlib>
#include <ctime>
#include <iostream>

// include order: base first
#include "kolokvijum.hpp"
#include "predmet.hpp"
#include "student.hpp"

int main() {
  // Seed random for Kolokvijum poeni
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  // === Create some tests ===
  Kolokvijum k1("Matematika");
  Kolokvijum k2("Programiranje");
  Kolokvijum k3("Elektronika");
  Kolokvijum k4("Fizika");

  // Print their details to verify random poeni
  std::cout << "=== Kreirani kolokvijumi ===\n";
  k1.ispis();
  k2.ispis();
  k3.ispis();
  k4.ispis();
  std::cout << "============================\n\n";

  // === Create 2 subjects (predmeti) ===
  Predmet p1("Racunarske mreze");
  Predmet p2("Objektno programiranje");

  // Add tests into them (by REFERENCE, as prof required)
  p1.dodajTest(k1);
  p1.dodajTest(k2);

  p2.dodajTest(k3);
  p2.dodajTest(k4);

  // Show subject details
  std::cout << "=== Ispis predmeta ===\n";
  p1.ispis();
  std::cout << "\n";
  p2.ispis();
  std::cout << "=======================\n\n";

  // === Create Student with two subjects ===
  Student s(p1, p2);

  // Print everything + comparison
  std::cout << "=== Student ispis ===\n";
  s.ispis();
  std::cout << "=====================\n";

  return 0;
}