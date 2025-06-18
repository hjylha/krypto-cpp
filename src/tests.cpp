
#include <string>
#include <map>
#include <vector>
#include <iostream>
// #include <ctime>
#include <chrono>
#include "basic_functions.h"
#include "file_operations.h"
#include "codewordpuzzle.h"
#include "test_functions.h"

using std::cout, std::endl, std::string, std::map, std::vector;

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();

    cout << "\nTesting basic_functions:" << endl;

    bool remove_whitespace_works = test_remove_whitespace();
    cout << "remove_whitespace works: " << remove_whitespace_works << endl;

    bool split_string_works = test_split_string();
    cout << "split_string works: " << split_string_works << endl;

    bool lowercase_works = test_lowercase();
    cout << "lowercase works: " << lowercase_works << endl;

    bool uppercase_works = test_uppercase();
    cout << "uppercase works: " << uppercase_works << endl;

    bool codeword_as_str_works = test_codeword_as_str();
    cout << "codeword_as_str works: " << codeword_as_str_works << endl;

    bool are_letters_in_alphabet_works = test_are_letters_in_alphabet();
    cout << "are_letters_in_alphabet works: " << are_letters_in_alphabet_works << endl;

    bool does_word_match_works = test_does_word_match();
    cout << "does_word_match works: " << does_word_match_works << endl;


    cout << "\nTesting file_operations:" << endl;

    string test_config_path = "test_config.conf";
    bool read_config_works = test_read_config(test_config_path);
    cout << "read_config works: " << read_config_works << endl;

    string test_language_file_path = "test_language_file.csv";
    bool get_language_map_works = test_get_language_map(test_language_file_path);
    cout << "get_language_map works: " << get_language_map_works << endl;

    string test_wordlist_path = "test_wordlist.txt";
    bool get_wordlist_works = test_get_wordlist(test_wordlist_path);
    cout << "get_wordlist works: " << get_wordlist_works << endl;

    string test_codeword_path = "test_codewords.csv";
    bool get_codewords_works = test_get_codewords(test_codeword_path);
    cout << "get_codewords works: " << get_codewords_works << endl;
    // vector<vector<int>> test_numbers = readCSVIntegers(test_filepath);
    // for (auto& row : test_numbers)
    // {
    //     for (int num : row) {
    //         cout << num << " ";
    //     }
    //     cout << endl;
    // }
    

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    cout << "\nTime elapsed to do things: " << duration.count() << " microseconds" << endl;

    return 0;
}