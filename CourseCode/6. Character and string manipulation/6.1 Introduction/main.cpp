#include <iostream>
#include <cctype>
#include <vector>
#include <string>

void checkBlank(char c) {
    if(std::isblank(c) == 1) {
        std::cout << c << " is blank." << std::endl;
    } else {
        std::cout << c << " is not blank." << std::endl;
    }
}

void checkAlnum(char c) {
    if(std::isalnum(c) == 1) {
        std::cout << c << " is alphanumeric." << std::endl;
    } else {
        std::cout << c << " is not alphanumeric." << std::endl;
    }
}

void checkAlpha(char c) {
    if(std::isalpha(c) == 1) {
        std::cout << c << " is alphabetic." << std::endl;
    } else {
        std::cout << c << " is not alphabetic." << std::endl;
    }
}

void countBlanks(const std::string s) {
    size_t blankCount{0};
    for(const auto& c : s) {
        if(std::isblank(c)) {
            ++blankCount;
        }
    }
    std::cout << "Number of blank characters: " << blankCount << std::endl;
}

void countUpper(std::string s) {
    size_t upperCount{0};
    
    for(auto& c : s) {
        if(std::isupper(c)){
            ++upperCount;
        }
    }

    std::cout << "Number of uppercase characters: " << upperCount << std::endl;
}

void countLower(std::string s) {
    size_t lowerCount{0};

    for(auto& c : s) {
        if(std::islower(c)){
            ++lowerCount;
        }
    }

    std::cout << "Number of lowercase characters: " << lowerCount << std::endl;
}

void toUpper(std::string s) {
    std::cout << "Original string: " << s << std::endl;
    
    for(auto& c : s) {
        c = std::toupper(c);
    }
    std::cout << "Uppercase string: " << s << std::endl;
}

int main() {
    std::cout << "std::isalnum: " << std::endl;
    char testChar{'*'};
    char alnumChar{'A'};

    checkAlnum(testChar);
    checkAlnum(alnumChar);
    std::cout << std::endl;

    std::cout << "std::isalpha: " << std::endl;
    char alphaChar{'A'};
    char nonAlphaChar{'1'};
    
    checkAlpha(alphaChar);
    checkAlpha(nonAlphaChar);
    std::cout << std::endl;

    std::cout << "std::isblank: " << std::endl;
    char notBlank{'A'};
    char blank{' '};

    checkBlank(notBlank);
    checkBlank(blank);
    std::cout << std::endl;

    std::string input{};
    std::cout << "Counting blank characters in a string: " << std::endl;
    std::cout << "Enter characters: ";
    
    std::getline(std::cin, input);

    countBlanks(input);

    std::cout << std::endl;

    std::string upperInput{};
    std::cout << "Counting uppercase characters in a string: " << std::endl;
    std::cout << "Enter characters: ";

    std::getline(std::cin, upperInput);

    countUpper(upperInput);

    std::cout << std::endl;

    std::string lowerInput{};
    std::cout << "Counting lowercase characters in a string: " << std::endl;
    std::cout << "Enter characters: ";

    std::getline(std::cin, lowerInput);
    
    countLower(lowerInput);

    std::cout << std::endl;

    std::string upperInput1{};
    std::cout << "Converting a string to uppercase: " << std::endl;
    std::cout << "Enter characters: ";

    std::getline(std::cin, upperInput1);

    toUpper(upperInput1);

    std::cout << std::endl;
    return 0;
}