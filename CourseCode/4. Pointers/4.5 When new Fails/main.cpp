#include <iostream>

int main() {
    //int *data = new int[10000000000000];

    /*
    for(size_t i{0}; i < 10000000; ++i) {
        int *data = new int[1000000];
    }
    */

    for(size_t i{0}; i < 10000000; ++i) {
        try{
            int *data = new int[1000000];
        } catch(std::exception& ex) {
            std::cout << "Exception caught: " << ex.what() << std::endl;
        }
    }

    std::cout << "Program completed successfully." << std::endl;

    return 0;
}