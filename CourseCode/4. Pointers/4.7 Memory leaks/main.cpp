#include <iostream>

int main() {
    int *pNumber {new int{64}};
    int number {128};
    // pNumber = &number; // This would cause a memory leak

    int *pNumber1 {new int{256}};
    // pNumber1 = new int{512}; // This would also cause a memory leak

    delete pNumber; // Free the memory allocated for 64
    delete pNumber1; // Free the memory allocated for 256
    pNumber = nullptr; // Avoid dangling pointer
    pNumber1 = nullptr; // Avoid dangling pointer

    return 0;
}