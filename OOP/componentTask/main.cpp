#include "checkbox.hpp"
#include "label.hpp"
#include "panel.hpp"
#include <iostream>

int main() {
  // === Individual components ===
  CheckBox cb1;                   // default ctor (0,0,false)
  CheckBox cb2(10.5, 20.5, true); // param ctor

  Label l1; // default ctor
  Label l2(5.0, 7.5, DinString("Hello world"));

  std::cout << "=== Test individual components ===\n";
  cb1.printComponent();
  std::cout << "Type: " << cb1.getTypeName() << "\n\n";

  cb2.printComponent();
  std::cout << "Type: " << cb2.getTypeName() << "\n\n";

  l1.printComponent();
  std::cout << "Type: " << l1.getTypeName() << "\n\n";

  l2.printComponent();
  std::cout << "Type: " << l2.getTypeName() << "\n\n";

  // Modify label text
  l2.setText(DinString("Updated text!"));

  std::cout << "=== After changing label text ===\n";
  l2.printComponent();
  std::cout << "\n";

  // === Panel with capacity 3 ===
  Panel p;
  std::cout << "Panel type: " << p.getTypeName() << "\n";

  std::cout << "\nAdding components to panel...\n";
  p.addComponent(cb1);
  p.addComponent(l2);
  p.addComponent(cb2);

  p.setCapacity(3);
  // Try over-capacity
  std::cout
      << "Adding another label beyond capacity (should fail when cap=3)…\n";
  bool added = p.addComponent(l1);
  std::cout << (added ? "Dodavanje uspešno\n" : "Nema mesta u panelu\n");

  // Print panel state
  std::cout << "\n=== Panel content ===\n";
  p.printComponent();
  std::cout << "\n";

  // Remove the 2nd component
  std::cout << "=== Remove component at position 2 ===\n";
  if (p.removeComponent(2)) {
    std::cout << "Uspešno uklonjena komponenta.\n";
  } else {
    std::cout << "Neuspešno uklanjanje.\n";
  }

  std::cout << "\n=== Panel content after remove ===\n";
  p.printComponent();

  return 0;
}