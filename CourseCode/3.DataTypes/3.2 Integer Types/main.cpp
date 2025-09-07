#include <iostream>

int main() {
    int elephantCount;
    int lionCount{};
    int dogCount{10};
    int catCount{20};

    int domesticAnimalCount{dogCount + catCount};

    std::cout << "Domesticated animal count: " << domesticAnimalCount << "\n";

    int appleCount(5);
    int orangeCount(10);
    int fruitCount(appleCount + orangeCount);

    int narrowingConversionFunctional(2.9);

    std::cout << "Fruit count: " << fruitCount << "\n";
    std::cout << "Narrowing conversion (functional): " << narrowingConversionFunctional << "\n";

    int bikeCount = 5;
    int truckCount = 10;
    int vehicleCount = bikeCount + truckCount;

    std::cout << "Vehicle count: " << vehicleCount << "\n";

    for(int i = 0; i < 5; ++i){
        std::cout << "Iteration: " << i << std::endl;
    }

    return 0;
}