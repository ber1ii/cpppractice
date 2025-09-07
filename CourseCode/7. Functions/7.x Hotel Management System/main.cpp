#include <iostream>
#include <string>
#include <vector>

enum class RoomType {
    Single,
    Double,
    Suite
};

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
void addRoom(std::vector<Room>& rooms);

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
                std::cout << "Display Rooms functionality not implemented yet.\n";
                break;
            case 3:
                std::cout << "Book Rooms functionality not implemented yet.\n";
                break;
            case 4:
                std::cout << "Cancel Reservations functionality not implemented yet.\n";
                break;
            case 5:
                std::cout << "Display Reservations functionality not implemented yet.\n";
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
    std::cout << "4. Cancel Reservations\n";
    std::cout << "5. Display Reservations\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
    
    std::cin >> choice;
    return choice;
}

void addRoom(std::vector<Room>& rooms) {
    Room newRoom;
    std::cout << "Enter room number: ";
    std::cin >> newRoom.roomNumber;

    size_t typeChoice{};
    std::cout << "Select room type (1. Single, 2. Double, 3. Suite): ";
    std::cin >> typeChoice;

    switch(typeChoice) {
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
