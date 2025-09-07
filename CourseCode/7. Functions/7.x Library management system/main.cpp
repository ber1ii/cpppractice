#include <iostream>
#include <string>
#include <vector>

struct Book {
    std::string title;
    std::string author;
    int year;
    bool isBorrowed;
};

int displayMenu();
void addBook(std::vector <Book>& library);
void displayBooks(const std::vector <Book>& library);
void borrowBook(std::vector <Book>& library);
void returnBook(std::vector <Book>& library);
void searchBooks(const std::vector <Book>& library);

int main() {
    std::vector<Book> library;
    bool running = true;

    while(running) {
        int choice = displayMenu();

        switch(choice) {
        case 1: {
            addBook(library);
            break;
        }
        case 2: {
            displayBooks(library);
            break;
        }
        case 3: {
            borrowBook(library);
            break;
        }
        case 4: {
            returnBook(library);
            break;
        }
        case 5: {
            searchBooks(library);
            break;
        }
        case 6: {
            std::cout << "Exiting the program.\n";
            running = false;
            break;
        }
        default: {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
    }

    return 0;
}

int displayMenu() {
    int choice{};
    std::cout << "\n";
    std::cout << "=========================\n";
    std::cout << "Library Menu:\n";
    std::cout << "1. Add Book\n";
    std::cout << "2. Display Books\n";
    std::cout << "3. Borrow Book\n";
    std::cout << "4. Return Book\n";
    std::cout << "5. Search Books\n";
    std::cout << "6. Exit\n";

    std::cout << "Choose an option: ";
    std::cin >> choice;

    return choice;
}

void addBook(std::vector<Book>& library) {
    Book newBook;
    
    std::cout << "Enter book title: ";
    std::cin.ignore();
    std::getline(std::cin, newBook.title);
    std::cout << "Enter book author: ";
    std::getline(std::cin, newBook.author);
    std::cout << "Enter publication year: ";
    std::cin >> newBook.year;
    
    newBook.isBorrowed = false;
    library.push_back(newBook);
    
    std::cout << "\nBook added successfully!\n\n";
}

void displayBooks(const std::vector<Book>& library) {
    if(library.empty()) {
        std::cout << "No books in the library.\n";
        return;
    } else {
        std::cout << "\nBooks in the library:\n\n";
        for(const auto& book : library) {
            std::cout << "Title: " << book.title;
            std::cout << ", Author: " << book.author;
            std::cout << ", Year: " << book.year;
            std::cout << ", Status: " << (book.isBorrowed ? "Borrowed" : "Available") << "\n";
        }
    }
}

void borrowBook(std::vector<Book>& library) {
    if(library.empty()) {
        std::cout << "No books available to borrow.\n";
        return;
    } else{
        bool found = false;

        std::cout << "\nAvailable books:\n\n";

        for(size_t i = 0; i < library.size(); i++) {
            if(library[i].isBorrowed == false) {
                std::cout << i + 1 << ". " << library[i].title << " by " << library[i].author << "\n";
                found = true;
            }
        }

        if(!found) {
            std::cout << "No books available to borrow.\n";
            return;
        }

        size_t choice{};

        std::cout << "Enter the index of the book you wish to borrow: ";
        std::cin >> choice;

        if(choice < 1 || choice > library.size() || library[choice - 1].isBorrowed) {
            std::cout << "Invalid choice or book already borrowed.\n";
        } else {
            library[choice - 1].isBorrowed = true;
            std::cout << "You have borrowed \"" << library[choice - 1].title << "\".\n";
        }
    }
}

void returnBook(std::vector <Book>& library) {
    if(library.empty()){
        std::cout << "No books in the library.\n";
        return;
    } else{
        bool found = false;

        std::cout << "\nList of borrowed books:\n\n";

        for(size_t i{0}; i < library.size(); i++){
            if(library[i].isBorrowed == true){
                std::cout << i + 1 << ". " << library[i].title << " by " << library[i].author << "\n";
                found = true;
            }
        }

        if(!found){
            std::cout << "No books are currently borrowed.\n";
            return;
        }

        size_t choice{};

        std::cout << "Enter the index of the book you wish to return: ";
        std::cin >> choice;

        if(choice < 1 || choice > library.size() || library[choice - 1].isBorrowed == false){
            std::cout << "Invalid choice or book was not borrowed.\n";
        } else {
            library[choice - 1].isBorrowed = false;
            std::cout << "You have returned \"" << library[choice - 1].title << "\".\n";
        }
    }
}

void searchBooks(const std::vector<Book>& library) {
    if(library.empty()) {
        std::cout << "No books in the library.\n";
        return;
    } else {
        std::string searchTerm;
        std::cout << "Enter title or author to search: ";
        std::cin.ignore();
        std::getline(std::cin, searchTerm);

        std::cout << "\nSearch results:\n\n";
        for(const auto& book : library) {
            if(book.title.find(searchTerm) != std::string::npos || book.author.find(searchTerm) != std::string::npos){
                std::cout << "Title: " << book.title;
                std::cout << ", Author: " << book.author;
                std::cout << ", Year: " << book.year;
                std::cout << ", Status: " << (book.isBorrowed ? "Borrowed" : "Available") << "\n";
            } else {
                std::cout << "No matching books found.\n";
            }
        }
    }
}