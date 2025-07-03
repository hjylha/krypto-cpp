
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <iostream>
// #include <ctime>
#include <chrono>
#include "basic_functions.h"
#include "file_operations.h"
#include "codewordpuzzle.h"
#include "test_functions.h"

using std::cout, std::endl, std::string, std::map, std::vector, std::pair;


void show_test_result(bool test_result, string test_description) {
    cout << test_result << "  " << test_description << endl;
}


int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();

    cout << "\nTesting basic_functions:" << endl;

    // bool remove_whitespace_works = test_remove_whitespace();
    // cout << "remove_whitespace works: " << remove_whitespace_works << endl;
    show_test_result(test_remove_whitespace(), "test_remove_whitespace");

    // bool split_string_works = test_split_string();
    // cout << "split_string works: " << split_string_works << endl;
    show_test_result(test_split_string(), "test_split_string");

    // bool lowercase_works = test_lowercase();
    // cout << "lowercase works: " << lowercase_works << endl;
    show_test_result(test_lowercase(), "test_lowercase");

    // bool uppercase_works = test_uppercase();
    // cout << "uppercase works: " << uppercase_works << endl;
    show_test_result(test_uppercase(), "test_uppercase");

    // bool codeword_as_str_works = test_codeword_as_str();
    // cout << "codeword_as_str works: " << codeword_as_str_works << endl;
    show_test_result(test_codeword_as_str(), "test_codeword_as_str");

    // bool mass_replace_works = test_mass_replace();
    // cout << "mass_replace works: " << mass_replace_works << endl;
    show_test_result(test_mass_replace(), "test_mass_replace");

    // bool get_nums_in_codewords_works = test_get_nums_in_codewords();
    // cout << "get_nums_in_codewords works: " << get_nums_in_codewords_works << endl;
    show_test_result(test_get_nums_in_codewords(), "test_get_nums_in_codewords");

    // bool are_letters_in_alphabet_works = test_are_letters_in_alphabet();
    // cout << "are_letters_in_alphabet works: " << are_letters_in_alphabet_works << endl;
    show_test_result(test_are_letters_in_alphabet(), "test_are_letters_in_alphabet");

    // bool does_word_match_works = test_does_word_match();
    // cout << "does_word_match works: " << does_word_match_works << endl;
    show_test_result(test_does_word_match(), "test_does_word_match");

    // bool get_matched_words_works = test_get_matched_words();
    // cout << "get_matched_words works: " << get_matched_words_works << endl;
    show_test_result(test_get_matched_words(), "test_get_matched_words");


    cout << "\nTesting file_operations:" << endl;

    // bool does_path_exist_works = test_does_path_exist();
    // cout << "does_path_exist works: " << does_path_exist_works << endl;
    show_test_result(test_does_path_exist(), "test_does_path_exist");

    string test_config_path = "test_config.conf";
    // bool read_config_works = test_read_config(test_config_path);
    // cout << "read_config works: " << read_config_works << endl;
    show_test_result(test_read_config(test_config_path), "test_read_config");

    string test_language_file_path = "test_language_file.csv";
    // bool get_language_map_works = test_get_language_map(test_language_file_path);
    // cout << "get_language_map works: " << get_language_map_works << endl;
    show_test_result(test_get_language_map(test_language_file_path), "test_get_language_map");

    string test_wordlist_path = "test_wordlist.txt";
    // bool get_wordlist_works = test_get_wordlist(test_wordlist_path);
    // cout << "get_wordlist works: " << get_wordlist_works << endl;
    show_test_result(test_get_wordlist(test_wordlist_path), "test_get_wordlist");

    string test_codeword_path = "test_codewords.csv";
    // bool get_codewords_works = test_get_codewords(test_codeword_path);
    // cout << "get_codewords works: " << get_codewords_works << endl;
    show_test_result(test_get_codewords(test_codeword_path), "test_get_codewords");

    // bool get_csv_files_in_folder_works = test_get_csv_files_in_folder();
    // cout << "get_csv_files_in_folder works: " << get_csv_files_in_folder_works << endl;
    show_test_result(test_get_csv_files_in_folder(), "test_get_csv_files_in_folder");

    
    cout << "\nTesting CodewordPuzzle:" << endl;

    // bool get_matching_indices_works = test_get_matching_indices();
    // cout << "get_matching_indices works: " << get_matching_indices_works << endl;
    show_test_result(test_get_matching_indices(), "test_get_matching_indices");

    // bool do_words_match_to_matching_indices_works = test_do_words_match_to_matching_indices();
    // cout << "do_words_match_to_matching_indices works: " << do_words_match_to_matching_indices_works << endl;
    show_test_result(test_do_words_match_to_matching_indices(), "test_do_words_match_to_matching_indices");

    // bool codeword_word_pair_works = test_CodewordWordPair();
    // cout << "CodewordWordPair works: " << codeword_word_pair_works << endl;
    show_test_result(test_CodewordWordPair(), "test_CodewordWordPair");

    pair<vector<string>, vector<vector<int>>> codewords_n_comments = get_codewords(test_codeword_path);
    vector<vector<int>> codewords = codewords_n_comments.second;
    vector<string> comments = codewords_n_comments.first;
    vector<string> wordlist = get_wordlist(test_wordlist_path);
    map<string, map<string, string>> config = read_config(test_config_path);
    string alphabet = config["tag"]["alphabet"];
    CodewordPuzzle puzzle = CodewordPuzzle(codewords, wordlist, alphabet, comments);

    // cout << "alphabet: " << alphabet << endl;
    // cout << "alphabet: " << puzzle.get_alphabet() << endl;
    
    // bool CodewordPuzzle_works = test_CodewordPuzzle(puzzle);
    // cout << "CodewordPuzzle works: " << CodewordPuzzle_works << endl;
    show_test_result(test_CodewordPuzzle(puzzle), "test_CodewordPuzzle");

    // bool substitution_vector_things_works = test_substitution_vector_things(puzzle);
    // cout << "substitution_vector_things works: " << substitution_vector_things_works << endl;
    show_test_result(test_substitution_vector_things(puzzle), "test_substitution_vector_things");

    

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    cout << "\nTime elapsed to test things: " << duration.count() << " microseconds" << endl;

    return 0;
}