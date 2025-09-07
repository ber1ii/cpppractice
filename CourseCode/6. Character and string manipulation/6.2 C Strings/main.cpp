#include <iostream>
#include <cstring>

int main() {
    const char message[]{"Hello, World!"};
    const char *message1{"The sky is blue"};

    std::cout << "strlen(message): " << std::strlen(message) << '\n'; // length of string, not counting the null terminator
    std::cout << "sizeof(message): " << sizeof(message) << '\n'; // size of array, but has the null terminator

    std::cout << "strlen(message1): " << std::strlen(message1) << '\n';
    std::cout << "sizeof(message1): " << sizeof(message1) << '\n'; // size of pointer

    const char *stringMessage{"Alabama"};
    const char *stringMessage2{"Blabama"};

    std::cout << "std::strcmp : (" << stringMessage << ", " << stringMessage2 << ") = " 
              << std::strcmp(stringMessage, stringMessage2) << '\n'; // negative value because 'A' < 'B'

    char stringMessage3[]{"Alabama"};
    char stringMessage4[]{"Alabama"};

    std::cout << "std::strcmp : (" << stringMessage3 << ", " << stringMessage4 << ") = " 
              << std::strcmp(stringMessage3, stringMessage4) << '\n'; // 0 because they are equal

    const char *stringMessage5{"Alabama"};
    const char *stringMessage6{"Alabbmb"};

    std::cout << "std::strncmp : (" << stringMessage5 << ", " << stringMessage6 << ", 3) = " 
              << std::strncmp(stringMessage5, stringMessage6, 3) << '\n'; // 0 because first 3 chars are equal

    std::cout << "std::strcnmp : (" << stringMessage << ", " << stringMessage2 << ", 3) = "
              << std::strncmp(stringMessage, stringMessage2, 3) << '\n'; // negative value because 'A' < 'B'

    std::cout << "std::strchr : " << std::endl;
    const char *stringMessage7{"Try not. Do or do not. There is no try"};
    char targetChar{'T'};
    const char *result = stringMessage7;
    size_t iterations{0};

    while((result = std::strchr(result, targetChar)) != nullptr) {
        std::cout << "Found '" << targetChar << "' starting at '" << result << "'\n";

        ++result; // advance pointer to avoid finding the same character again
        ++iterations;
    }

    std::cout << "Iterations: " << iterations << '\n';

    return 0;
}