#pragma once
#include "visitor.hpp"

class ChildVisitor : public Visitor {
private:
  DinString parentID;

public:
  ChildVisitor() : Visitor(), parentID("") {}
  ChildVisitor(int ticketNumber, MovieType type, const DinString &id,
               const DinString &name, const DinString &parentID)
      : Visitor(ticketNumber, type, id, name), parentID(parentID) {}
  ChildVisitor(const Visitor &base, const DinString parentID)
      : Visitor(base), parentID(parentID) {}

  DinString toString() const override {
    DinString ret = "Child: ";
    ret += Visitor::toString();
    ret += "Parent ID: ";
    ret += parentID;
    return ret;
  }

  ~ChildVisitor() override {}
};