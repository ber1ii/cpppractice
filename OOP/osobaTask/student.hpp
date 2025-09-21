#pragma once
#include "osoba.hpp"

class Student : public Osoba {
private:
  int brIndex;

public:
  Student() : Osoba(), brIndex(0) {}
  Student(const DinString &ime, const DinString &prezime, int brIndex)
      : Osoba(ime, prezime), brIndex(brIndex) {}
  Student(const Student &student)
      : Osoba(student.ime, student.prezime), brIndex(student.brIndex) {}

  void ispis() const override {
    Osoba::ispis();
    std::cout << " Broj Indexa: " << brIndex;
  }
};