#pragma once
#include "visitor.hpp"

class ChildVisitor : public Visitor {
private:
  DinString parentId;

public:
  ChildVisitor(int ticketNumber, AnimalType type, const DinString &id,
               const DinString &name, int age, const DinString &parentId)
      : Visitor(ticketNumber, type, id, name, age), parentId(parentId) {}

  ChildVisitor(const Visitor &v, const DinString &parentId)
      : Visitor(v), parentId(parentId) {}

  DinString getParentId() const { return parentId; }

  DinString toString() const override {
    DinString ret;
    ret = "Child: ";
    ret += Visitor::toString();
    ret += " Parent id: ";
    ret += parentId;

    return ret;
  }

  ~ChildVisitor() {}
};