#pragma once
#include "component.hpp"
#include "list.hpp"

class Panel : public Component {
private:
  static DinString typeName;
  int capacity;
  List<Component *> components;

public:
  Panel() : capacity(10) {}
  Panel(const Panel &p) : capacity(p.capacity), components(p.components) {}
  Panel(int capacity) : capacity(capacity) {}

  DinString getTypeName() const override { return typeName; }

  void setCapacity(int cap) { capacity = cap; }

  void printComponent() override {
    Component::printComponent();
    std::cout << "Lista komponenata: \n";

    for (int i = 1; i <= components.size(); i++) {
      Component *c;

      components.read(i, c);
      std::cout << "Komponenta #" << i << "\n";
      c->printComponent();
      std::cout << "\nType: " << c->getTypeName() << "\n";
      std::cout << "----------------\n";
    }
  }

  bool addComponent(Component &c) {
    if (components.size() < capacity) {
      components.add(components.size() + 1, &c);
      return true;
    }
    return false;
  }

  bool removeComponent(int i) {
    if (i >= 1 && i <= components.size()) {
      components.remove(i);
      return true;
    }
    return false;
  }
};