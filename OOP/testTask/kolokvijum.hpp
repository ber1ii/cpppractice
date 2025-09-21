#pragma once
#include "test.hpp"

class Kolokvijum : public Test {
public:
  Kolokvijum() : Test(DinString(""), 0) {}
  Kolokvijum(const char *naziv) : Test(DinString(naziv), rand() % 25 + 1) {}

  int getPoeni() const override { return osvojeniPoeni; }

  bool polozio() const override {
    if (osvojeniPoeni > 12) {
      return true;
    }
    return false;
  }
};