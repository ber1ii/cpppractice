#pragma once
#include "childFan.hpp"
#include "fan.hpp"
#include "list.hpp"

enum class StadiumState { OPEN, CLOSED };

template <MatchType TYPE, int SEATS, int DURATION> class Stadium {
private:
  List<Fan *> queue;
  StadiumState state;
  int totalFans;
  int totalMinutes;

public:
  Stadium() : state(StadiumState::CLOSED), totalFans(0), totalMinutes(0) {}

  void open() {
    state = StadiumState::OPEN;
    totalMinutes = 0;
    totalFans = 0;
  }

  void close() {
    state = StadiumState::CLOSED;
    queue.clear();
  }

  bool addFan(Fan *f) {
    if (f->getMatchType() != TYPE) {
      return false;
    }

    for (int i = 1; i <= queue.size(); i++) {
      Fan *existing;

      queue.read(i, existing);
      if (f->getId() == existing->getId()) {
        return false;
      }
    }

    ChildFan *cf = dynamic_cast<ChildFan *>(f);

    if (cf != nullptr) {
      bool guardianFound = false;

      for (int i = 1; i <= queue.size(); i++) {
        Fan *potentialGuardian;

        queue.read(i, potentialGuardian);
        if (potentialGuardian->getId() == cf->getGuardianId()) {
          guardianFound = true;
          break;
        }
      }

      if (!guardianFound) {
        return false;
      }
    }

    if (ChildFan *cf = dynamic_cast<ChildFan *>(f)) {
      bool guardianFound = false;
      for (int i = 1; i <= queue.size(); i++) {
        Fan *potentialGuardian;
        queue.read(i, potentialGuardian);
        if (potentialGuardian->getId() == cf->getGuardianId()) {
          guardianFound = true;
          break;
        }
      }
      if (!guardianFound) {
        return false;
      }
    } else {
      if (TYPE == MatchType::FOOTBALL && f->getAge() < 16) {
        return false;
      }
    }

    queue.add(queue.size() + 1, f);
    return true;
  }

  int queueSize() const { return queue.size(); }

  bool seatBatch() {
    if (state == StadiumState::CLOSED || queue.empty()) {
      return false;
    }

    int fanBatchSize = std::min(SEATS, queue.size());

    for (int i = 0; i < fanBatchSize; i++) {
      queue.remove(1);
    }

    totalFans += fanBatchSize;
    totalMinutes += DURATION;

    return true;
  }

  DinString convertStadiumString() const {
    if (state == StadiumState::OPEN) {
      return DinString("OPEN");
    } else {
      return DinString("CLOSED");
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const Stadium &stadium) {
    os << "Type: ";
    switch (TYPE) {
    case MatchType::FOOTBALL:
      os << DinString("FOOTBALL");
      break;
    case MatchType::BASKETBALL:
      os << DinString("BASKETBALL");
      break;
    case MatchType::TENNIS:
      os << DinString("TENNIS");
      break;
    }

    os << "\nRide state: " << stadium.convertStadiumString();
    os << "\nSeats available: " << SEATS;
    os << "\nDuration per match: " << DURATION;
    os << "\nTotal fans: " << stadium.totalFans;
    os << "\nTotal working time(hours): " << stadium.totalMinutes / 60.0f;

    if (!stadium.queue.empty()) {
      os << "\nQueue: ";

      for (int i = 1; i <= stadium.queue.size(); i++) {
        Fan *f;

        stadium.queue.read(i, f);
        os << "\n - " << *f;
      }
    }

    os << "\n---------------";

    return os;
  }
};