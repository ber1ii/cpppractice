#include "profesor.hpp"
#include "student.hpp"
#include "ucionica.hpp"

int main() {
  Student s1("Ilong", "Ma", 1);
  Profesor p1("Neil Degrasse", "Tyson", "Astrofizika");

  Ucionica u1("Amfiteatar", 5);

  u1.ispis();

  u1.dodajOsobu(s1);
  u1.dodajOsobu(p1);

  u1.ispis();
  return 0;
}