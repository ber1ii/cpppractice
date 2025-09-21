#pragma once
#include "component.hpp"

class Label : public Component {
private:
  DinString text;
  static DinString typeName;

public:
  Label() : Component(0, 0), text(DinString("")) {}
  Label(double x, double y, const DinString &text)
      : Component(x, y), text(text) {}

  DinString getTypeName() const override { return typeName; }
  DinString getText() const { return text; }
  void setText(const DinString &newText) { text = newText; }

  void printComponent() override {
    Component::printComponent();
    std::cout << "\nVrednost polja text: " << text << std::endl;
  }
};