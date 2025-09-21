#pragma once
#include "dinstring.hpp"
#include <iostream>

class Component {
protected:
  double x;
  double y;

public:
  Component() : x(0), y(0) {}
  Component(double x, double y) : x(x), y(y) {}

  double getX() const { return x; }
  double getY() const { return y; }

  virtual void printComponent() { std::cout << "X: " << x << ", Y: " << y; }

  virtual DinString getTypeName() const = 0;
};