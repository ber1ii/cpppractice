#pragma once
#include "component.hpp"

class CheckBox : public Component {
private:
  bool pressed;
  static DinString typeName;

public:
  CheckBox() : Component(0, 0), pressed(false) {}
  CheckBox(double x, double y, bool pressed)
      : Component(x, y), pressed(pressed) {}

  DinString getTypeName() const override { return typeName; }

  void printComponent() override {
    Component::printComponent();
    std::cout << "\nVrednost polja pressed: " << (pressed ? "true" : "false")
              << std::endl;
  }
};