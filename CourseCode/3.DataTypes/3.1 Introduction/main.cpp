#include <iostream>

int main() {
    int a{15};
    int b{017};
    int c{0xf};
    int d{0b1111};

    std::cout << "Number a in decimal: " << a << std::endl;
    std::cout << "Number b in octal (017): " << b << std::endl;
    std::cout << "Number c in hexadecimal (0xf): " << c << std::endl;
    std::cout << "Number d in binary (0b1111): " << d << std::endl;
    std::cout << "Size of int: " << sizeof(int) << std::endl;    
    
    return 0;
}

