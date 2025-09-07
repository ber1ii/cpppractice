#include <iostream>

int main() {
    int *pNumber{nullptr};
    pNumber = new int; // Dynamically allocate an integer
    *pNumber = 42;     // Assign a value to the allocated memory

    std::cout << "Dynamically allocating memory to integer: " << std::endl;
    std::cout << "Value: " << *pNumber << std::endl;
    std::cout << "Address: " << pNumber << std::endl;

    delete pNumber; // Free the allocated memory
    pNumber = nullptr; // Avoid dangling pointer
    
    return 0;
}