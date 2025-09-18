#pragma once
#include "visitor.hpp"

class ChildVisitor : public Visitor {
private:
  DinString parentId;

public:
  ChildVisitor() : Visitor(), parentId("") {}
  ChildVisitor(int ticketNumber, RideType type, const DinString &id,
               const DinString &name, const DinString &parentId)
      : Visitor(ticketNumber, type, id, name), parentId(parentId) {}

  ChildVisitor(const Visitor &v, const DinString &parentId)
      : Visitor(v), parentId(parentId) {}

  DinString getParentId() const { return parentId; }

  DinString toString() const override {
    DinString ret = "Child: ";
    ret += Visitor::toString();
    ret += " Parent Id: ";
    ret += parentId;
    return ret;
  }

  ~ChildVisitor() {}
};