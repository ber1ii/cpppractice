#include <iostream>
#include <string>

using namespace std; // Avoid using 'using namespace std;' in real projects

int main() {
    const char *pMessage { "Hello, World!" }; // Pointer to a string literal, not modifiable
    
    std::cout << pMessage << std::endl;
    std::cout << *pMessage << std::endl; // Print the first character of the string

    //Allow users to modify the string
    char message[] {"Hello, World!"};
    message[0] = 'h';
    std::string message2 {"Hello, World!"};
    message2[0] = 'b';

    std::cout<< message << std::endl;
    std::cout<< message2 << std::endl;

    return 0;
}