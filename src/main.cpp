
#include <string>
#include <vector>
#include <iostream>
// #include <ctime>
#include <chrono>
#include "codewordpuzzle.h"
#include "file_operations.h"

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();

    std::cout << "Hello world!" << std::endl;

    std::string test_filepath = "test.csv";
    std::vector<std::vector<int>> test_numbers = readCSVIntegers(test_filepath);
    for (auto& row : test_numbers)
    {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Time elapsed to do things: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
