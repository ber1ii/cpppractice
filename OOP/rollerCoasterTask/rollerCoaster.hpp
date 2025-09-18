#pragma once
#include "childVisitor.hpp"
#include "dinstring.hpp"
#include "list.hpp"
#include "visitor.hpp"

enum class RideState { OPEN, CLOSED };

template <RideType TYPE, int CAPACITY, int DURATION> class RollerCoaster {
private:
  List<Visitor *> queue;
  RideState state;
  int totalRiders;
  int totalMinutes;

public:
  RollerCoaster() : state(RideState::CLOSED), totalRiders(0), totalMinutes(0) {}

  void open() {
    state = RideState::OPEN;
    totalRiders = 0;
    totalMinutes = 0;
  }

  void close() {
    state = RideState::CLOSED;
    queue.clear();
  }

  bool addVisitor(Visitor *v) {
    if (v->getRideType() != TYPE) {
      return false;
    }

    for (int i = 1; i <= queue.size(); i++) {
      Visitor *existing;

      queue.read(i, existing);
      if (existing->getId() == v->getId()) {
        return false;
      }
    }

    ChildVisitor *cv = dynamic_cast<ChildVisitor *>(v);

    if (cv != nullptr) {
      bool parentFound = false;
      for (int i = 1; i <= queue.size(); i++) {
        Visitor *potentialParent;

        queue.read(i, potentialParent);
        if (potentialParent->getId() == cv->getParentId()) {
          parentFound = true;
          break;
        }
      }
      if (!parentFound) {
        return false;
      }
    }

    queue.add(queue.size() + 1, v);
    return true;
  }

  int queueSize() const { return queue.size(); }

  bool runRide() {
    if (state == RideState::CLOSED || queue.empty()) {
      return false;
    }

    int numCurrentRiders = std::min(CAPACITY, queue.size());

    for (int i{}; i < numCurrentRiders; i++) {
      Visitor *v;

      queue.read(1, v);
      queue.remove(1);
    }

    totalRiders += numCurrentRiders;
    totalMinutes += DURATION;

    return true;
  }

  DinString convertRideState(RideState state) const {
    if (state == RideState::OPEN) {
      return DinString("OPEN");
    } else {
      return DinString("CLOSED");
    }
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const RollerCoaster &rollerCoaster) {
    os << "--- Roller Coaster ---\n";
    os << "Ride Type: ";
    switch (TYPE) {
    case RideType::THRILL:
      os << DinString("THRILL");
      break;
    case RideType::FAMILY:
      os << DinString("FAMILY");
      break;
    case RideType::KIDS:
      os << DinString("KIDS");
      break;
    }

    os << " Capacity: " << CAPACITY;
    os << ", Duration: " << DURATION;
    os << ", state: " << rollerCoaster.convertRideState(rollerCoaster.state);
    os << ", total duration (hours): " << rollerCoaster.totalMinutes / 60.0f;
    os << ", total riders: " << rollerCoaster.totalRiders;

    if (!rollerCoaster.queue.empty()) {
      os << "\nQueue: ";
      for (int i = 1; i <= rollerCoaster.queue.size(); i++) {
        Visitor *v;
        rollerCoaster.queue.read(i, v);
        os << "\n - " << *v;
      }
    }

    os << "\n------------";

    return os;
  }
};
