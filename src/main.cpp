
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
// #include <ctime>
#include <locale>
#include <clocale>
#include <chrono>
#include "file_operations.h"
#include "codewordpuzzle.h"
#include "codewordpuzzle_cli.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "utf-8");
    // std::locale::global(std::locale("utf-8"));
    // std::cout.imbue(std::locale());

    // auto start_time = std::chrono::high_resolution_clock::now();
    std::string lang = "";
    std::string cw_path = "";

    // std::cout << argc << " command line arguments detected:" << std::endl;
    // for (int i = 0; i < argc; i++) {
    //     std::cout << argv[i] << std::endl;
    // }

    PuzzleCLI puzzle_cli = PuzzleCLI();
    std::vector<std::string> languages = puzzle_cli.get_languages();
    for (int i = 1; i < argc; i++) {
        if (std::find(languages.begin(), languages.end(), argv[i]) != languages.end()) {
            lang = argv[i];
            continue;
        }
        if (does_path_exist(argv[i])) {
            cw_path = argv[i];
        }
    }


    puzzle_cli.input_data_and_initialize_puzzle(lang, cw_path);

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
