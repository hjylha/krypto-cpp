
#include <string>
#include <map>
#include <vector>
#include <iostream>
// #include <ctime>
#include <chrono>
#include "codewordpuzzle.h"
#include "file_operations.h"
#include "test_functions.h"

using std::cout, std::endl, std::string, std::map, std::vector;

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();

    cout << "Hello world!" << endl;

    string test_config_path = "test_config.conf";
    bool read_config_works = test_read_config(test_config_path);

    cout << "read_config works: " << read_config_works << endl;

    string test_filepath = "test_codewords";
    vector<vector<int>> test_numbers = readCSVIntegers(test_filepath);
    for (auto& row : test_numbers)
    {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    cout << "Time elapsed to do things: " << duration.count() << " microseconds" << endl;

    return 0;
}