#include <iostream>

int main() {
    std::cout << std::endl;
    std::cout << "Verbose nullptr check: " << std::endl;

    int *pNumber{};
    pNumber = new int(6);

    if(!(pNumber==nullptr)) {
        std::cout << "pNumber points to a valid address" << std::endl;
        std::cout << "pNumber = " << *pNumber << std::endl;
    } else {
        std::cout << "pNumber points to an invalid address" << std::endl;
    }

    delete pNumber;
    pNumber = nullptr;

    return 0;
}