#pragma once
#include <iostream>

class Employee {
private:
  int hoursWorked;
  double salary;

public:
  Employee(int h = 0, double s = 0) : hoursWorked(h), salary(s) {}
  Employee(const Employee &e) : hoursWorked(e.hoursWorked), salary(e.salary) {}

  int getHours() const { return hoursWorked; }
  double getSalary() const { return salary; }

  void setSalary(double s) { salary = s; }

  void addHours(int h) {
    hoursWorked += h;
    if (hoursWorked > 300) {
      hoursWorked = 300;
    }
  }
  void reset() {
    hoursWorked = 0;
    salary = 0;
  }

  void print() const {
    std::cout << "Hours worked: " << hoursWorked << ", Salary: " << salary
              << std::endl;
  }
};