#pragma once
#include "dinstring.hpp"
#include <iostream>

enum class MovieType { ACTION, COMEDY, ANIMATION };

class MovieTicket {
private:
  int ticketNumber;
  MovieType type;

public:
  MovieTicket() : ticketNumber(), type(MovieType::ACTION) {}
  MovieTicket(int tN, MovieType t) : ticketNumber(tN), type(t) {}

  int getTicketNumber() const { return ticketNumber; }
  MovieType getMovieType() const { return type; }

  DinString convertMovieTypeToString(MovieType type) const {
    switch (type) {
    case MovieType::ACTION:
      return DinString("ACTION");
    case MovieType::COMEDY:
      return DinString("COMEDY");
    case MovieType::ANIMATION:
      return DinString("ANIMATION");
    }
    return DinString("UNKNOWN");
  }

  friend std::ostream &operator<<(std::ostream &os, const MovieTicket &ticket) {
    os << "Ticket Number: " << ticket.ticketNumber
       << ", Movie Type: " << ticket.convertMovieTypeToString(ticket.type);

    return os;
  }
};