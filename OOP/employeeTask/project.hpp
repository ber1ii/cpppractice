#pragma once
#include "employee.hpp"
#include <cstdlib>
#include <iostream>

enum class ProjectState { UNASSIGNED, ASSIGNED, WORKING, COMPLETED };

class Project {
private:
  Employee e;
  ProjectState currentState;
  constexpr static int MAX_SALARY = 5000;
  constexpr static int MAX_HOURS = 300;

public:
  Project() : e(0, 0), currentState(ProjectState::UNASSIGNED) {}
  Project(int h, double s, ProjectState cS) : e(h, s), currentState(cS) {}

  bool assignEmployee() {
    if (currentState == ProjectState::UNASSIGNED) {
      currentState = ProjectState::ASSIGNED;

      return true;
    }
    return false;
  }

  bool removeEmployee() {
    if (currentState != ProjectState::UNASSIGNED &&
        currentState != ProjectState::COMPLETED) {
      e.reset();
      currentState = ProjectState::UNASSIGNED;
      return true;
    }
    return false;
  }

  bool startWork(int hours) {
    if ((currentState == ProjectState::ASSIGNED ||
         currentState == ProjectState::WORKING) &&
        e.getHours() < MAX_HOURS) {
      currentState = ProjectState::WORKING;
      e.addHours(hours);

      return true;
    }
    return false;
  }

  bool paySalary(double amount) {
    if (currentState == ProjectState::WORKING) {
      double newSalary;

      newSalary = amount + e.getSalary();
      if (newSalary > static_cast<double>(MAX_SALARY)) {
        newSalary = static_cast<double>(MAX_SALARY);
      }

      e.setSalary(newSalary);
      return true;
    }
    return false;
  }

  bool completeProject() {
    if (e.getHours() >= 120 && e.getSalary() >= 3000) {
      currentState = ProjectState::COMPLETED;
      return true;
    }
    return false;
  }

  bool giveBonus() {
    int min = 200;
    int max = 500;
    int randomNumber = min + (std::rand() % (max - min + 1));

    if (currentState == ProjectState::WORKING && e.getHours() >= 160) {
      double newSalary;
      newSalary = e.getSalary() + randomNumber;

      if (newSalary > static_cast<double>(MAX_SALARY)) {
        newSalary = MAX_SALARY;

        e.setSalary(newSalary);
        return true;
      }
      e.setSalary(newSalary);

      std::cout << "Bonus granted: +" << randomNumber << " salary."
                << std::endl;
      return true;
    }
    return false;
  }

  friend void printProject(const Project &p);
};

inline void printProject(const Project &p) {
  std::cout << "===== PROJECT VIEW =====" << std::endl;
  p.e.print();

  switch (p.currentState) {
  case ProjectState::UNASSIGNED:
    std::cout << "UNASSIGNED";
    break;
  case ProjectState::ASSIGNED:
    std::cout << "ASSIGNED";
    break;
  case ProjectState::WORKING:
    std::cout << "WORKING";
    break;
  case ProjectState::COMPLETED:
    std::cout << "COMPLETED";
    break;
  }

  std::cout << std::endl;
}