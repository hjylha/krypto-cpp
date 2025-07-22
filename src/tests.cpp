
#include <clocale>
#include <locale>
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
    setlocale(LC_ALL, "utf-8");
    // std::locale::global(std::locale(""));
    // std::cout.imbue(std::locale());

    // string something = "I \U0001F60D \u03A9";
    // std::u32string something32 = "I \U0001F60D \u03A9";

    // cout << "\'" << something << "\' is " << something.length() << " characters long" << endl;
    // cout << "\'" << something32 << "\' is " << something32.length() << " characters long" << endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    cout << "\nTesting basic_functions:" << endl;

    show_test_result(test_get_minimum(), "test_get_minimum");

    // bool remove_whitespace_works = test_remove_whitespace();
    // cout << "remove_whitespace works: " << remove_whitespace_works << endl;
    show_test_result(test_remove_whitespace(), "test_remove_whitespace");

    show_test_result(test_add_whitespace(), "test_add_whitespace");

    show_test_result(test_add_whitespace2(), "test_add_whitespace2");

    // bool split_string_works = test_split_string();
    // cout << "split_string works: " << split_string_works << endl;
    show_test_result(test_split_string(), "test_split_string");

    show_test_result(test_utf8_split(), "test_utf8_split");

    show_test_result(test_join_string(), "test_join_string");

    // bool lowercase_works = test_lowercase();
    // cout << "lowercase works: " << lowercase_works << endl;
    show_test_result(test_lowercase(), "test_lowercase");

    show_test_result(test_lowercase_nonascii(), "test_lowercase_nonascii");

    // bool uppercase_works = test_uppercase();
    // cout << "uppercase works: " << uppercase_works << endl;
    show_test_result(test_uppercase(), "test_uppercase");

    show_test_result(test_uppercase_nonascii(), "test_uppercase_nonascii");

    show_test_result(test_find_string(), "test_find_string");

    show_test_result(test_find_int(), "test_find_int");

    // bool codeword_as_str_works = test_codeword_as_str();
    // cout << "codeword_as_str works: " << codeword_as_str_works << endl;
    show_test_result(test_codeword_as_str(), "test_codeword_as_str");

    show_test_result(test_get_alphabet_map(), "test_get_alphabet_map");

    // bool mass_replace_works = test_mass_replace();
    // cout << "mass_replace works: " << mass_replace_works << endl;
    show_test_result(test_mass_replace(), "test_mass_replace");

    // bool get_nums_in_codewords_works = test_get_nums_in_codewords();
    // cout << "get_nums_in_codewords works: " << get_nums_in_codewords_works << endl;
    show_test_result(test_get_nums_in_codewords(), "test_get_nums_in_codewords");

    // bool are_letters_in_alphabet_works = test_are_letters_in_alphabet();
    // cout << "are_letters_in_alphabet works: " << are_letters_in_alphabet_works << endl;
    show_test_result(test_are_letters_in_alphabet(), "test_are_letters_in_alphabet");

    show_test_result(test_are_letters_in_alphabet2(), "test_are_letters_in_alphabet2");

    // bool does_word_match_works = test_does_word_match();
    // cout << "does_word_match works: " << does_word_match_works << endl;
    show_test_result(test_does_word_match(), "test_does_word_match (öljytynnyri fails)");

    show_test_result(test_does_word_match2(), "test_does_word_match2");

    // bool get_matched_words_works = test_get_matched_words();
    // cout << "get_matched_words works: " << get_matched_words_works << endl;
    show_test_result(test_get_matched_words(), "test_get_matched_words (öljytynnyri fails)");

    show_test_result(test_get_matched_words2(), "test_get_matched_words2");


    cout << "\nTesting file_operations:" << endl;

    // bool does_path_exist_works = test_does_path_exist();
    // cout << "does_path_exist works: " << does_path_exist_works << endl;
    show_test_result(test_does_path_exist(), "test_does_path_exist");

    show_test_result(test_does_path_exist_folder_edition(), "test_does_path_exist_folder_edition (fails in windows?)");

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

    show_test_result(test_get_wordlist_vector(test_wordlist_path), "test_get_wordlist_vector");

    show_test_result(test_get_wordlist_as_int_vector(test_wordlist_path), "test_get_wordlist_as_int_vector");

    show_test_result(test_get_wordlist_as_int_vector_plus(test_wordlist_path), "test_get_wordlist_as_int_vector_plus");

    string test_codeword_path = "test_codewords.csv";
    // bool get_codewords_works = test_get_codewords(test_codeword_path);
    // cout << "get_codewords works: " << get_codewords_works << endl;
    show_test_result(test_get_codewords(test_codeword_path), "test_get_codewords");

    show_test_result(test_get_codewords_and_comments(test_codeword_path), "test_get_codewords_and_comments");

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
    // vector<string> wordlist = get_wordlist(test_wordlist_path);
    vector<vector<string>> wordlist = get_wordlist_vector(test_wordlist_path);
    map<string, map<string, string>> config = read_config(test_config_path);
    // string alphabet = config["tag"]["alphabet"];
    vector<string> alphabet = utf8_split(config["tag"]["alphabet"]);
    CodewordPuzzle puzzle = CodewordPuzzle(codewords, wordlist, alphabet, comments);

    // cout << "alphabet: " << alphabet << endl;
    // cout << "alphabet: " << puzzle.get_alphabet() << endl;
    
    // bool CodewordPuzzle_works = test_CodewordPuzzle(puzzle);
    // cout << "CodewordPuzzle works: " << CodewordPuzzle_works << endl;
    show_test_result(test_CodewordPuzzle(puzzle), "test_CodewordPuzzle");

    // bool substitution_vector_things_works = test_substitution_vector_things(puzzle);
    // cout << "substitution_vector_things works: " << substitution_vector_things_works << endl;
    show_test_result(test_substitution_vector_things(puzzle), "test_substitution_vector_things");

    show_test_result(test_sort_codewords(puzzle), "test_sort_codewords");

    show_test_result(test_match_two_codewords(puzzle), "test_match_two_codewords");

    show_test_result(test_find_all_unique_pairs(puzzle), "test_find_all_unique_pairs");


    cout << "\nTesting CodewordPuzzle1:" << endl;

    show_test_result(test_do_words_match_to_matching_indices_int(), "test_do_words_match_to_matching_indices_int");

    show_test_result(test_CodewordWordPair1(), "test_CodewordWordPair1");

    CodewordsAndComments comments_and_codewords = get_codewords_and_comments(test_codeword_path);
    map<string, int> alphabet_map = get_alphabet_map(config["tag"]["alphabet"]);
    pair<vector<int>, vector<vector<int>>> wordlist_n_lengths = get_wordlist_as_int_vector_plus(test_wordlist_path, alphabet_map);
    CodewordPuzzle1 puzzle1 = CodewordPuzzle1(comments_and_codewords.codewords,
        comments_and_codewords.codeword_lengths, 
        wordlist_n_lengths.second, 
        wordlist_n_lengths.first, 
        alphabet.size(), 
        comments_and_codewords.comments);

    show_test_result(test_CodewordPuzzle1(puzzle1), "test_CodewordPuzzle1");

    show_test_result(test_substitution_vector_things1(puzzle1), "test_substitution_vector_things1");

    show_test_result(test_sort_codewords1(puzzle1), "test_sort_codewords1");

    show_test_result(test_match_two_codewords1(puzzle1), "test_match_two_codewords1");

    show_test_result(test_find_all_unique_pairs1(puzzle1), "test_find_all_unique_pairs1");


    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    cout << "\nTime elapsed to test things: " << duration.count() << " microseconds" << endl;

    return 0;
}