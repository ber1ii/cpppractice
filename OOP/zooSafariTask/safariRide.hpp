#pragma once
#include "childVisitor.hpp"
#include "list.hpp"
#include "visitor.hpp"

enum class RideState { OPEN, CLOSED };

template <AnimalType TYPE, int JEEP_CAPACITY, int DURATION> class SafariRide {
private:
  List<Visitor *> queue;
  RideState state;
  int totalRiders;
  int totalMinutes;

public:
  SafariRide() : state(RideState::CLOSED), totalRiders(0), totalMinutes(0) {}

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
    if (v->getAnimalType() != TYPE) {
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
        if (cv->getParentId() == potentialParent->getId()) {
          parentFound = true;
          break;
        }
      }

      if (!parentFound) {
        return false;
      }
    }

    if (ChildVisitor *cv = dynamic_cast<ChildVisitor *>(v)) {
      bool parentFound = false;
      for (int i = 1; i <= queue.size(); i++) {
        Visitor *potentialParent;
        queue.read(i, potentialParent);
        if (potentialParent->getId() == cv->getParentId()) {
          parentFound = true;
          break;
        }
      }
      if (!parentFound)
        return false;
    } else {
      if (TYPE == AnimalType::CARNIVORE && v->getAge() < 18) {
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

    int ridersThisRide = std::min(JEEP_CAPACITY, queue.size());

    for (int i{}; i < ridersThisRide; i++) {
      Visitor *v;

      queue.read(1, v);
      queue.remove(1);
    }

    totalRiders += ridersThisRide;
    totalMinutes += DURATION;

    return true;
  }

  DinString convertRideState() const {
    if (state == RideState::OPEN) {
      return DinString("OPEN");
    } else {
      return DinString("CLOSED");
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const SafariRide &safari) {
    os << "Ride Type: ";

    switch (TYPE) {
    case AnimalType::CARNIVORE:
      os << DinString("CARNIVORE");
      break;
    case AnimalType::HERBIVORE:
      os << DinString("HERBIVORE");
      break;
    case AnimalType::BIRD:
      os << DinString("BIRD");
      break;
    }

    os << "\nJeep capacity: " << JEEP_CAPACITY;
    os << "\nDuration of one ride: " << DURATION;
    os << "\nTotal riders: " << safari.totalRiders;
    os << "\nTotal duration (hours): " << safari.totalMinutes / 60.0f;
    os << "\nRide State: " << safari.convertRideState();

    if (!safari.queue.empty()) {
      os << "\nQueue: ";

      for (int i = 1; i <= safari.queue.size(); i++) {
        Visitor *v;

        safari.queue.read(i, v);
        os << "\n - " << *v;
      }
    }

    os << "\n--------------";

    return os;
  }
};