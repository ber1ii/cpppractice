#pragma once
#include "dinstring.hpp"
#include "list.hpp"
#include "visitor.hpp"

enum class CinemaState { OPEN, CLOSED };

template <MovieType GENRE, int SEATS, int RUNTIME> class Cinema {
private:
  List<Visitor *> queue;
  CinemaState state;
  int totalVisitors;
  int totalMinutes;

public:
  Cinema() : state(CinemaState::CLOSED), totalVisitors(0), totalMinutes(0) {}

  void open() {
    state = CinemaState::OPEN;
    totalVisitors = 0;
    totalMinutes = 0;
  }

  void close() {
    state = CinemaState::CLOSED;
    queue.clear();
  }

  bool addVisitor(Visitor *v) {
    if (v->getMovieType() != GENRE) {
      return false;
    }

    for (int i = 1; i <= queue.size(); i++) {
      Visitor *existing;

      queue.read(i, existing);
      if (existing->getID() == v->getID()) {
        return false;
      }
    }

    queue.add(queue.size() + 1, v);
    return true;
  }

  int queueSize() const { return queue.size(); }

  bool runScreening() {
    if (state == CinemaState::CLOSED || queue.empty()) {
      return false;
    }

    int visitorsInThisScreening = std::min(SEATS, queue.size());

    for (int i{}; i < visitorsInThisScreening; i++) {
      Visitor *v;
      queue.read(1, v);
      queue.remove(1);
    }

    totalVisitors += visitorsInThisScreening;
    totalMinutes += RUNTIME;

    return true;
  }

  DinString cinemaStateToString(CinemaState state) const {
    if (state == CinemaState::OPEN) {
      return DinString("OPEN");
    } else {
      return DinString("CLOSED");
    }

    return DinString("UNKNOWN");
  }

  friend std::ostream &operator<<(std::ostream &os, const Cinema &c) {
    os << "--- Cinema ---\n";
    os << "Genre: ";
    switch (GENRE) {
    case MovieType::ACTION:
      os << DinString("ACTION");
      break;
    case MovieType::COMEDY:
      os << DinString("COMEDY");
      break;
    case MovieType::ANIMATION:
      os << DinString("ANIMATION");
      break;
    }

    os << "\nSeats per screening: " << SEATS
       << "\nMinutes per screening: " << RUNTIME
       << "\nCinema state: " << c.cinemaStateToString(c.state)
       << "\nTotal viewers: " << c.totalVisitors << "\nTotal runtime(hours): "
       << static_cast<float>(static_cast<float>(c.totalMinutes) / 60)
       << "\nVisitors waiting: " << c.queue.size();

    if (!c.queue.empty()) {
      os << "\nQueue: ";
      for (int i = 1; i <= c.queue.size(); i++) {
        Visitor *v;
        c.queue.read(i, v);
        os << "\n - " << *v;
      }
    }

    os << "\n------------";
    return os;
  }
};