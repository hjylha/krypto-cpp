
#include <string>
#include <vector>
#include <iostream>
// #include <ctime>
#include <chrono>
#include "file_operations.h"
#include "codewordpuzzle.h"
#include "codewordpuzzle_cli.h"

int main()
{
    // auto start_time = std::chrono::high_resolution_clock::now();

    std::cout << "Hello world!" << std::endl;

    PuzzleCLI puzzle_cli = PuzzleCLI();
    puzzle_cli.input_data_and_initialize_puzzle("", "");

    puzzle_cli.print_initial_info();
    std::cout << std::endl;

    while (puzzle_cli.running) {
        std::cout << std::endl;
        puzzle_cli.choose_main_choice();
    }
    

    // auto end_time = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // std::cout << "Time elapsed to do things: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
