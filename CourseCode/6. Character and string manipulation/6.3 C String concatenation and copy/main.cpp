#include <iostream>
#include <cstring>

int main() {
    std::cout << "std::strcat : " << std::endl;

    char dest[50] = "Hello, ";
    char src[50] = "World!";

    std::strcat(dest, src);
    std::cout << dest << std::endl;

    std::strcat(dest, " How are you?");
    std::cout << dest << std::endl;

    char *dest1 = new char[30]{'F', 'o', 'o', ' ', '\0'};
    char *src1 = new char[30]{'F', 'i', 'g','h', 't', 'e', 'r', 's', '\0'};

    std::cout << "Length of dest1 before strcat: " << std::strlen(dest1) << std::endl;
    std::cout << "Length of src1 before strcat: " << std::strlen(src1) << std::endl;

    std::strcat(dest1, src1);
    std::cout << dest1 << std::endl;

    std::cout << "Length of dest1 after strcat: " << std::strlen(dest1) << std::endl;
    std::cout << "Length of src1 after strcat: " << std::strlen(src1) << std::endl;

    std::cout << "std::strncat : " << std::endl;

    char dest2[50] = "Hello, ";
    char src2[30] = "There! is a bird on the tree.";

    std::strncat(dest2, src2, 6);
    std::cout << dest2 << std::endl;

    char *dest3 = new char[30]{'G', 'e', 'n', 'e', 'r', 'a', 'l', ' ', '\0'};
    char *src3 = new char[30]{'K', 'e', 'n', 'o', 'b', 'i', '\0'};

    std::strcat(dest3, src3);
    std::cout << dest3 << std::endl;

    std::cout << "std::strcpy : " << std::endl;

    const char *src4 = "Hello, there! General Kenobi.";
    char *dest4 = new char[std::strlen(dest3) + 1];

    std::strcpy(dest4, src4);

    std::cout << dest4 << std::endl;
    std::cout << "Length of dest4 after strcpy: " << std::strlen(dest4) << std::endl;
    std::cout << "sizeof() dest4: " << sizeof(dest4) << std::endl;

    return 0;
}