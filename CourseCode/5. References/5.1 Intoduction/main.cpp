#include <iostream>

int main() {
    int intValue{42};
    double doubleValue{3.14};

    int& intRef{intValue};
    double& doubleRef{doubleValue};

    return 0;
}