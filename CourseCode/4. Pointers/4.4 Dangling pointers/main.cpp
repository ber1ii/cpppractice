#include <iostream>

int main() {
    int *pNumber{new int{56}};

    std::cout << "pNumber before delete: " << *pNumber << std::endl;

    delete pNumber;

    //std::cout << "pNumber after delete: " << *pNumber << std::endl; // Undefined behavior

    pNumber = nullptr; // Avoid dangling pointer

    int *pNumber1{new int{78}};
    int *pNumber2{pNumber1}; // Both pointers point to the same memory

    std::cout << "pNumber1: " << *pNumber1 << " Address: " << pNumber1 << std::endl;
    std::cout << "pNumber2: " << *pNumber2 << " Address: " << pNumber2 << std::endl;

    delete pNumber1;
    pNumber1 = nullptr;

    //pNumber2 is now a dangling pointer
    //std::cout << "pNumber2 after delete pNumber1: " << *pNumber2 << std::endl; // Undefined behavior

    pNumber2 = nullptr; // Avoid dangling pointer

    int *pNumber3{nullptr};
    int *pNumber4{new int{90}};

    if(pNumber4 != nullptr) {
        std::cout << "pNumber4: " << *pNumber4 << std::endl;
        delete pNumber4;
        pNumber4 = nullptr;
    } else{
        std::cout << "Invalid address" << std::endl;
    }

    return 0;
}