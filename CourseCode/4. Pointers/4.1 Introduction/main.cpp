#include <iostream>

int main() {

    // Using C++23 standard for pointer initialization
    int *pNumber{}; // pNumber is initialized to nullptr
    double *pFractionalNumber{};

    // Explicitly initializing pointers to nullptr
    int *pNumber1{nullptr}; // Explicitly initialized to nullptr
    double *pFractionalNumber1{nullptr};

    std::cout << "Size of int: " << sizeof(int) << std::endl;
    std::cout << "Size of double: " << sizeof(double) << std::endl;
    std::cout << "Size of double pointer: " << sizeof(double*) << std::endl;
    std::cout << "Size of int pointer: " << sizeof(int*) << std::endl;
    std::cout << "Size of pNumber: " << sizeof(pNumber) << std::endl;
    std::cout << "Size of pFractionalNumber: " << sizeof(pFractionalNumber) << std::endl;
    std::cout << "Size of pNumber1: " << sizeof(pNumber1) << std::endl;
    std::cout << "Size of pFractionalNumber1: " << sizeof(pFractionalNumber1) << std::endl;

    int *pNumber2{}, otherVar{}; // pNumber2 is a pointer initialized to nullptr, otherVar is an int initialized to 0
    std::cout << "Size of pNumber2: " << sizeof(pNumber2) << "\n Size of otherVar: " << sizeof(otherVar) << std::endl;

    int* pNumber3{}, otherVar1{}; // pNumber3 is a pointer initialized to nullptr, otherVar1 is an int initialized to 0
    std::cout << "Size of pNumber3: " << sizeof(pNumber3) << "\n Size of otherVar1: " << sizeof(otherVar1) << std::endl;

    int int_var{42};
    int *ptrIntVar{&int_var}; // Pointer initialized to the address of int_var
    std::cout << "Value of int_var: " << int_var << std::endl;
    std::cout << "Address of int_var: " << ptrIntVar << std::endl;

    int int_var1{65};
    ptrIntVar = &int_var1; // Pointer now points to the address of int_var1
    std::cout << "Value of int_var1: " << int_var1 << std::endl;
    std::cout << "Address of int_var1: " << ptrIntVar << std::endl;

    //Dereferencing pointer to get the value
    int *ptrIntVar2{nullptr};
    int intData{55};
    ptrIntVar2 = &intData; // Pointer now points to the address of int
    std::cout << "Value of intData: " << *ptrIntVar2 << std::endl; // Dereferencing pointer to get the value of intData

    return 0;
}