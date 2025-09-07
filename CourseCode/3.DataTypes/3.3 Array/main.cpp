#include <iostream>
#include <vector>

int main() {
    int n{};

    std::cout << "Enter number of elements: " <<std::endl;
    std::cin >> n;

    std::vector<int> array(n);

    for (int i = 0; i < n; i++){
        std::cout << "Enter element " << i + 1 << ": ";
        std::cin >> array[i];
    }

    std::cout << "The array you entered: ";
    for (const auto& element : array) {
        std::cout << element << " ";
    }

    std::cout << "The array you entered (reversed): ";
    for (int i = n - 1; i >=0; i--){
        std::cout << array[i] << " ";
    }

    std::cout << "Sum of all elements: ";
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += array[i];
    }
    std::cout << sum << std::endl;
    std::cout << "Size of the array: " << array.size() << std::endl;

    return 0;
}