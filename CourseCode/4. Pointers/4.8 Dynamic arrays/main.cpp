#include <iostream>
#include <vector>

int main() {
    size_t size{10};

    double *pArray {new double[size]}; //Garbage values
    int *pArray2 { new(std::nothrow) int[size]{} }; //Initialized to zero
    double *pArray3 { new(std::nothrow) double[size]{1.0, 2.0, 3.0} }; //First three values initialized, rest to zero

    if(pArray3) {
        for(size_t i{0}; i < size; ++i) {
            std::cout << "Value: " << pArray3[i] << ":[" << i << "]" << std::endl;
        }
        std::cout << std::endl;
        delete[] pArray3;
    } else {
        std::cerr << "Memory allocation failed for pArray3" << std::endl;
    }

    delete[] pArray;
    delete[] pArray2;
    pArray2 = nullptr;
    pArray = nullptr;
    pArray3 = nullptr;

    return 0;
}