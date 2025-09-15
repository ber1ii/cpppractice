#include "employee.hpp"
#include "project.hpp"
#include <ctime>
#include <iostream>

int main() {
  Employee e1;
  Employee e2(70, 1600);
  Employee e3(e2);
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  e1.addHours(100);
  e1.print();

  e1.reset();
  e1.print();

  e2.print();
  e2.setSalary(2600);
  e2.print();
  std::cout << "Getter checks, getHours(e3): " << e3.getHours()
            << " getSalary(e3): " << e3.getSalary() << std::endl;

  std::cout << "=======================" << std::endl;
  std::cout << "TESTING PROJECT" << std::endl;

  Project p1;
  Project p2(130, 3000, ProjectState::WORKING);
  std::cout << "Printing project 2, all tests below are with project 1"
            << std::endl;
  printProject(p2);

  p2.startWork(200);
  std::cout << "Attempting to add over 200hours to 130 (MAX 300)" << std::endl;
  printProject(p2);

  p1.assignEmployee();
  std::cout << "Assigning employee" << std::endl;
  printProject(p1);

  p1.removeEmployee();
  printProject(p1);
  std::cout << "Trying to remove already removed employee: " << std::endl;
  p1.removeEmployee();
  printProject(p1);
  std::cout << "Trying to pay salary of unworking project" << std::endl;
  p1.paySalary(6000);
  printProject(p1);
  std::cout << "Trying to complete project without met conditions" << std::endl;
  p1.completeProject();
  printProject(p1);

  p1.assignEmployee();
  p1.startWork(170);
  std::cout << "Added 170 hours: " << std::endl;
  printProject(p1);

  p1.paySalary(3000);
  std::cout << "Increased salary to 3000" << std::endl;
  printProject(p1);

  p1.giveBonus();
  std::cout << "Applied bonus" << std::endl;
  printProject(p1);

  p1.paySalary(6000);
  std::cout << "Attempting to add 6000 to salary (MAX 5000)" << std::endl;
  printProject(p1);

  p1.giveBonus();
  std::cout << "Attempting to apply bonus over 5000" << std::endl;
  printProject(p1);

  p1.completeProject();
  printProject(p1);
}