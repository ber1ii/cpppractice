#include <iostream>
#include <vector>

void countLegalGuests(std::vector<int> age);

int main() {
    int n{};

    std::cout << "Enter number of guests: ";
    std::cin >> n;

    std::vector<int> age(n);
    
    for(int i = 0; i < n; i++) {
        std::cout << "Enter age of guest " << i + 1 << ": ";
        std::cin >> age[i];
        std::cout << "Guest " << i + 1 << " is " << age[i] << " years old." << std::endl;
    }

    countLegalGuests(age);

    return 0;
}

void countLegalGuests(std::vector<int> age) {
    size_t count = 0;
    for(size_t i=0; i<age.size(); i++) {
        if(age[i] >= 18) {
            count++;
        }
    }

    std::cout << "Number of legal guests: " << count << std::endl;
}
