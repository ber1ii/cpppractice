#include <iostream>
#include <limits>
#include <string>
#include <vector>

enum class RoomType { Single, Double, Suite };

struct Room {
  int roomNumber;
  RoomType type;
  double pricePerNight;
  bool isAvailable;
};

struct Reservation {
  std::string guestName;
  int roomNumber;
  int nights;
  double totalCost;
};

int displayMenu();
void addRoom(std::vector<Room> &rooms);
std::string roomTypeToString(RoomType type);
void displayRooms(const std::vector<Room> &rooms);
void displayAvailableRooms(const std::vector<Room> &rooms);
void bookRooms(std::vector<Room> &rooms,
               std::vector<Reservation> &reservations);
void displayReservations(const std::vector<Reservation> &reservations);
void cancelReservations(std::vector<Room> &rooms,
                        std::vector<Reservation> &reservations);

int main() {
  std::vector<Room> rooms;
  std::vector<Reservation> reservations;

  std::cout << "Welcome to the Hotel Reservation System!\n";

  bool running = true;
  while (running) {
    int choice = displayMenu();
    switch (choice) {
    case 1:
      addRoom(rooms);
      break;
    case 2:
      displayRooms(rooms);
      break;
    case 3:
      bookRooms(rooms, reservations);
      break;
    case 4:
      displayReservations(reservations);
      break;
    case 5:
      cancelReservations(rooms, reservations);
      break;
    case 6:
      std::cout << "Exiting the system. Goodbye!\n";
      running = false;
      break;
    default:
      std::cout << "Invalid choice. Please try again.\n";
    }
  }

  return 0;
}

int displayMenu() {
  int choice;

  std::cout << "Hotel Reservation System Menu:\n";
  std::cout << "1. Add Room\n";
  std::cout << "2. Display Rooms\n";
  std::cout << "3. Book Rooms\n";
  std::cout << "4. Display Reservations\n";
  std::cout << "5. Cancel Reservations\n";
  std::cout << "6. Exit\n";
  std::cout << "Enter your choice: ";

  std::cin >> choice;
  return choice;
}

void addRoom(std::vector<Room> &rooms) {
  Room newRoom;
  std::cout << "Enter room number: ";
  std::cin >> newRoom.roomNumber;

  for (const auto &room : rooms) {
    if (room.roomNumber == newRoom.roomNumber) {
      std::cout << "Error: Room number " << newRoom.roomNumber
                << " already exists!!!" << std::endl;
      return;
    }
  }

  size_t typeChoice{};
  std::cout << "Select room type (1. Single, 2. Double, 3. Suite): ";
  std::cin >> typeChoice;

  switch (typeChoice) {
  case 1:
    newRoom.type = RoomType::Single;
    newRoom.pricePerNight = 100.0;
    break;
  case 2:
    newRoom.type = RoomType::Double;
    newRoom.pricePerNight = 150.0;
    break;
  case 3:
    newRoom.type = RoomType::Suite;
    newRoom.pricePerNight = 250.0;
    break;
  default:
    std::cout << "Invalid room type selected.\n";
    return;
  }

  newRoom.isAvailable = true;
  rooms.push_back(newRoom);

  std::cout << "Room added successfully!\n";
}

std::string roomTypeToString(RoomType type) {
  switch (type) {
  case RoomType::Single:
    return "Single";
  case RoomType::Double:
    return "Double";
  case RoomType::Suite:
    return "Suite";
  default:
    return "Unknown";
  }
}

void displayRooms(const std::vector<Room> &rooms) {
  if (rooms.empty()) {
    std::cout << "There are no rooms to display!" << std::endl;
  } else {
    for (const auto &room : rooms) {
      std::cout << "Room number: " << room.roomNumber;
      std::cout << ", Type: " << roomTypeToString(room.type);
      std::cout << ", Price Per Night: " << room.pricePerNight;
      std::cout << ", Availability: "
                << (room.isAvailable ? "Available" : "Booked") << std::endl;
    }
  }
}

void displayAvailableRooms(const std::vector<Room> &rooms) {
  bool found = false;

  for (size_t i{}; i < rooms.size(); ++i) {
    if (rooms[i].isAvailable) {
      std::cout << i + 1 << ". Room number: " << rooms[i].roomNumber
                << ", Type: " << roomTypeToString(rooms[i].type)
                << ", Price: " << rooms[i].pricePerNight << std::endl;
      found = true;
    }
  }

  if (!found) {
    std::cout << "No rooms available at this moment!" << std::endl;
  }
}

void bookRooms(std::vector<Room> &rooms,
               std::vector<Reservation> &reservations) {
  if (rooms.empty()) {
    std::cout << "There are no rooms to book!" << std::endl;
    return;
  } else {

    displayAvailableRooms(rooms);

    size_t choice{};
    std::string guestName;
    Reservation newReservation;
    size_t nights{};
    double totalCost{};

    std::cout << "Choose a room to book: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice < 1 || choice > rooms.size() || !rooms[choice - 1].isAvailable) {
      std::cout << "Invalid choice. Please try again." << std::endl;
      return;
    }

    std::cout << "Enter your name: ";
    std::getline(std::cin, guestName);
    std::cout << std::endl;

    newReservation.guestName = guestName;
    newReservation.roomNumber = rooms[choice - 1].roomNumber;
    rooms[choice - 1].isAvailable = false;

    std::cout << "Enter the number of nights you wish to stay: ";
    std::cin >> nights;

    newReservation.nights = nights;
    totalCost = nights * rooms[choice - 1].pricePerNight;
    newReservation.totalCost = totalCost;

    reservations.push_back(newReservation);

    std::cout << "Room " << rooms[choice - 1].roomNumber
              << " has been succesfully booked for " << guestName << "!\n";
  }
}

void displayReservations(const std::vector<Reservation> &reservations) {
  if (reservations.empty()) {
    std::cout << "There are no reservations!" << std::endl;
  } else {
    for (size_t i{}; i < reservations.size(); ++i) {
      std::cout << i + 1
                << ". reservation. Guest: " << reservations[i].guestName
                << ", roomNumber: " << reservations[i].roomNumber << " "
                << reservations[i].nights
                << " nights. Total price: " << reservations[i].totalCost
                << std::endl;
    }
  }
}

void cancelReservations(std::vector<Room> &rooms,
                        std::vector<Reservation> &reservations) {

  if (reservations.empty()) {
    std::cout << "No reservations to cancel!" << std::endl;
    return;
  }

  displayReservations(reservations);

  size_t choice{};
  std::cout << "Enter the number of the reservation you want to cancel: ";
  std::cin >> choice;

  if (choice < 1 || choice > reservations.size()) {
    std::cout << "Invalid choice" << std::endl;
    return;
  }

  int roomNum = reservations[choice - 1].roomNumber;
  for (auto &room : rooms) {
    if (room.roomNumber == roomNum) {
      room.isAvailable = true;
      break;
    }
  }

  std::cout << "Reservation for guest " << reservations[choice - 1].guestName
            << "room " << reservations[choice - 1].roomNumber
            << ") has been cancelled. \n";

  reservations.erase(reservations.begin() + (choice - 1));
}