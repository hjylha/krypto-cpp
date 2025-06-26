
#include <filesystem>
#include <ostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include "basic_functions.h"
#include "file_operations.h"
#include "codewordpuzzle.h"

using std::string, std::map, std::vector, std::pair;


bool test_remove_whitespace() {
    bool passing = true;
    std::string expected_result = "hello";
    
    std::string text = "  hello   ";
    bool passing1 = remove_whitespace(text) == expected_result;
    passing *= passing1;

    text = "\nhello\t";
    bool passing2 = remove_whitespace(text) == expected_result;
    passing *= passing2;

    text = " \n \thello  \r";
    bool passing3 = remove_whitespace(text) == expected_result;
    passing *= passing3;

    text = " \nno \n way\t";
    expected_result = "no \n way";
    bool passing4 = remove_whitespace(text) == expected_result;
    passing *= passing4;

    return passing;
}

bool test_add_whitespace() {
    string text = "hello";
    int total_length = 7;
    string expected_text = "hello  ";
    bool passing = add_whitespace(text, total_length) == expected_text;

    text = "world";
    total_length = 4;
    expected_text = "worl";
    bool passing1 = add_whitespace(text, total_length) == expected_text;
    passing *= passing1;

    text = "longer";
    total_length = 10;
    expected_text = "longer    ";
    bool passing2 = add_whitespace(text, total_length) == expected_text;
    passing *= passing2;

    text = "uncharacteristic";
    total_length = 16;
    expected_text = "uncharacteristic";
    bool passing3 = add_whitespace(text, total_length) == expected_text;
    passing *= passing3;

    return passing;
}

bool test_split_string() {
    bool passing = true;

    string text = "abc,def,ghi";
    char delimiter = ',';
    vector<string> expected_result = {"abc", "def", "ghi"};
    bool passing1 = split_string(text, delimiter) == expected_result;
    passing *= passing1;

    text = "  ;123";
    delimiter = ';';
    expected_result = {"  ", "123"};
    bool passing2 = split_string(text, delimiter) == expected_result;
    passing *= passing2;

    return passing;
}

bool test_lowercase() {
    string text = "AbCdEfG";
    string expected_text = "abcdefg";
    bool passing = lowercase(text) == expected_text;

    text = "abc123D e F";
    expected_text = "abc123d e f";
    bool passing1 = lowercase(text) == expected_text;
    passing *= passing1;

    return passing;
}

bool test_uppercase() {
    string text = "AbCdEfG";
    string expected_text = "ABCDEFG";
    bool passing = uppercase(text) == expected_text;

    text = "abc123D e F";
    expected_text = "ABC123D E F";
    bool passing1 = uppercase(text) == expected_text;
    passing *= passing1;

    return passing;
}

bool test_codeword_as_str() {
    vector<int> codeword = {1, 1, 1, 1};
    string expected_text = "1,1,1,1";
    bool passing = codeword_as_str(codeword) == expected_text;

    codeword = {1, 2, 3};
    expected_text = "1,2,3";
    bool passing1 = codeword_as_str(codeword) == expected_text;
    passing *= passing1;

    codeword = {25, 30, 10, 0};
    expected_text = "25,30,10,0";
    bool passing2 = codeword_as_str(codeword) == expected_text;
    passing *= passing2;

    return passing;
}

bool test_mass_replace() {
    string text = "he%1%o";
    vector<string> replacements = {"ll"};
    string expected_text = "hello";
    bool passing = mass_replace(text, replacements) == expected_text;

    text = "w%1%r%2%d";
    replacements = {"o", "l"};
    expected_text = "world";
    bool passing1 = mass_replace(text, replacements) == expected_text;
    passing *= passing1;

    text = "something %1% %2% strange %3%";
    replacements = {"NOT", "particularly", "at all"};
    expected_text = "something NOT particularly strange at all";
    bool passing2 = mass_replace(text, replacements) == expected_text;
    passing *= passing2;

    text = "%1% me %2% others";
    replacements = {"1"};
    replacements.push_back("(2, 3)");
    expected_text = "1 me (2, 3) others";
    bool passing3 = mass_replace(text, replacements) == expected_text;
    passing *= passing3;

    return passing;
}

bool test_get_nums_in_codewords() {
    vector<vector<int>> codewords;
    codewords.push_back({1, 2, 3, 4, 5, 6});
    codewords.push_back({3, 7, 9});
    codewords.push_back({8, 10, 11});
    codewords.push_back({10, 12, 13});
    codewords.push_back({3, 22, 24, 15});
    codewords.push_back({21, 15, 13, 11});
    vector<int> expected_nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 21, 22, 24};
    bool passing = get_nums_in_codewords(codewords) == expected_nums;
    return passing;
}

bool test_are_letters_in_alphabet() {
    string text = "abcdefghijklmnopqrstuvwxyz";
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    bool passing = are_letters_in_alphabet(text, alphabet);

    text = "abc";
    alphabet = "def";
    bool passing1 = !(are_letters_in_alphabet(text, alphabet));
    passing *= passing1;

    text = "no?";
    alphabet = "abcdefghijklmnopqrstuvwxyz";
    bool passing2 = !(are_letters_in_alphabet(text, alphabet));
    passing *= passing2;

    text = "yes?";
    alphabet = "abcdefghijklmnopqrstuvwxyz?";
    bool passing3 = are_letters_in_alphabet(text, alphabet);
    passing *= passing3;

    text = "älämölö";
    alphabet = "abcdefghijklmnopqrstuvwxyzåäö";
    bool passing4 = are_letters_in_alphabet(text, alphabet);
    passing *= passing4;

    return passing;
}

bool test_does_word_match() {
    string word = "hello";
    vector<int> codeword = {1, 2, 3, 3, 4};
    bool passing = does_word_match(word, codeword);

    word = "world";
    codeword = {1, 2, 3, 4, 2};
    bool passing1 = !(does_word_match(word, codeword));
    passing *= passing1;

    return passing;
}

bool test_get_matched_words() {
    vector<int> codeword = {1, 2, 3, 3, 4};
    vector<string> wordlist = {"hello", "world", "tiny", "english", "abccd"};
    vector<string> expected_words = {"hello", "abccd"};
    bool passing = get_matched_words(codeword, wordlist, -1) == expected_words;
    return passing;
}


bool test_does_path_exist() {
    string current_work_directory = std::filesystem::current_path().string();
    bool passing = does_path_exist(current_work_directory);

    string existing_file = "test_codewords.csv";
    bool passing1 = does_path_exist(existing_file);
    passing *= passing1;

    string non_existing_file = "file_does_not_exists_here.txt";
    bool passing2 = !does_path_exist(non_existing_file);
    passing *= passing2;

    string existing_directory = "test_folder/";
    bool passing3 = does_path_exist(existing_directory);
    passing *= passing3;

    string existing_test_file = "test_folder/test.csv";
    bool passing4 = does_path_exist(existing_test_file);
    passing *= passing4;

    return passing;
}

bool test_read_config(string test_default_filepath)
{
    map<string, map<string, string>> config = read_config(test_default_filepath);
    // string default_language;

    bool passing = true;

    string lang1 = "tag";
    string lang2 = "another_tag";
    bool passing1 = config[lang1]["name"] == "default";
    bool passing2 = config[lang1]["alphabet"] == "abcdefg";
    bool passing3 = config[lang1]["wordlist_path"] == "test_stuff/test_wordlist";
    bool passing4 = config[lang1]["codeword_folder_path"] == "test_stuff";
    passing = passing && passing1 && passing2 && passing3 && passing4;

    bool passing5 = config[lang2]["name"] == "second";
    bool passing6 = config[lang2]["alphabet"] == "abcdefghijklmnopqrstuvwxyzåäö";
    bool passing7 = config[lang2]["wordlist_path"] == "";
    bool passing8 = config[lang2]["codeword_folder_path"] == "";
    passing = passing && passing5 && passing6 && passing7 && passing8;
    return passing;
}


bool test_get_language_map(string test_language_file_path)
{
    bool passing = true;
    map<string, map<string, string>> language_map = get_language_map(test_language_file_path);

    string lang_fi = "fi";
    string lang_en = "en";
    string key1 = "yes";
    string key2 = "no";

    bool passing1 = language_map[lang_fi][key1] == "kyllä";
    passing *= passing1;

    bool passing2 = language_map[lang_en][key1] == key1;
    passing *= passing2;

    bool passing3 = language_map[lang_fi][key2] == "ei";
    passing *= passing3;

    bool passing4 = language_map[lang_en][key2] == key2;
    passing *= passing4;

    return passing;
}

bool test_get_wordlist(string test_wordlist_path) {
    vector<string> wordlist = get_wordlist(test_wordlist_path);
    vector<string> expected_wordlist = {"some", "words", "here", "to", "be", "read", "by", "someone", "or", "something", "cola", "camp"};

    bool passing = wordlist == expected_wordlist;

    return passing;
}

bool test_get_codewords(string test_codeword_path) {
    bool passing = true;
    vector<string> expected_comments = {"this is a comment", "another line"};
    vector<vector<int>> expected_codewords;
    expected_codewords.push_back({1, 2, 3, 4, 5, 6});
    expected_codewords.push_back({3, 7, 9});
    expected_codewords.push_back({8, 10, 11});
    expected_codewords.push_back({10, 12, 13});
    expected_codewords.push_back({3, 22, 24, 15});
    expected_codewords.push_back({21, 15, 13, 11});

    pair<vector<string>, vector<vector<int>>> result = get_codewords(test_codeword_path);

    bool passing1 = result.first == expected_comments;
    passing *= passing1;

    vector<vector<int>> actual_codewords = result.second;

    bool passing2 = actual_codewords[0] == expected_codewords[0];
    passing *= passing2;

    bool passing3 = actual_codewords[1] == expected_codewords[1];
    passing *= passing3;

    bool passing4 = actual_codewords[2] == expected_codewords[2];
    passing *= passing4;

    return passing;
}

bool test_get_csv_files_in_folder() {
    string folder_path = "";
    vector<string> csv_files = get_csv_files_in_folder(folder_path);

    // for (auto p: csv_files) {
    //     std::cout << p << std::endl;
    // }

    string first_file = "test_codewords.csv";
    bool passing = csv_files[0].substr(csv_files[0].length() - first_file.length(), first_file.length()) == first_file;
    string second_file = "test_language_file.csv";
    bool passing1 = csv_files[1].substr(csv_files[1].length() - second_file.length(), second_file.length()) == second_file;
    passing *= passing1;

    folder_path = "test_folder/";
    csv_files = get_csv_files_in_folder(folder_path);
    string only_file = "test.csv";
    bool passing2 = csv_files[0].substr(csv_files[0].length() - only_file.length(), only_file.length()) == only_file;
    passing *= passing2;

    return passing;
}


bool test_get_matching_indices() {
    vector<int> codeword1 = {1, 1};
    vector<int> codeword2 = {2, 2};
    MatchingIndicesAndOthers exp_match_ind_n_othr({}, {0}, {0});
    MatchingIndicesAndOthers match_ind_n_othr = get_matching_indices(codeword1, codeword2);
    bool passing = exp_match_ind_n_othr == match_ind_n_othr;

    codeword1 = {1, 2};
    codeword2 = {2, 1};
    exp_match_ind_n_othr = MatchingIndicesAndOthers({pair<int, int>(0, 1), pair<int, int>(1, 0)}, {}, {});
    bool passing1 = exp_match_ind_n_othr == get_matching_indices(codeword1, codeword2);
    passing *= passing1;

    codeword1 = {1, 2, 3, 3, 4};
    codeword2 = {3, 5, 6, 2};
    exp_match_ind_n_othr = MatchingIndicesAndOthers({pair<int, int>(1, 3), pair<int, int>(2, 0)}, {0, 4}, {1, 2});
    bool passing2 = exp_match_ind_n_othr == get_matching_indices(codeword1, codeword2);
    passing *= passing2;

    return passing;
}

bool test_do_words_match_to_matching_indices() {
    string word1 = "hello";
    string word2 = "live";
    vector<pair<int, int>> matching_indices = {pair<int, int>(1, 3), pair<int, int>(2, 0)};
    vector<int> indices_in_word1 = {0, 4};
    vector<int> indices_in_word2 = {1, 2};
    MatchingIndicesAndOthers match_ind_n_othr(matching_indices, indices_in_word1, indices_in_word2);
    bool passing = do_words_match_to_matching_indices(word1, word2, match_ind_n_othr);
    return passing;
}


bool test_CodewordWordPair() {
    vector<int> codeword1 = {};
    vector<int> codeword2 = {};
    string word1 = "";
    string word2 = "";
    CodewordWordPair cw_w_pair = CodewordWordPair(codeword1, codeword2, word1, word2);

    bool passing = cw_w_pair.codeword1 == codeword1;
    bool passing1 = cw_w_pair.codeword2 == codeword2;
    passing *= passing1;

    bool passing2 = cw_w_pair.word1 == word1;
    passing *= passing2;
    bool passing3 = cw_w_pair.word2 == word2;
    passing *= passing3;

    return passing;
}

bool test_CodewordPuzzle(CodewordPuzzle puzzle) {
    vector<string> expected_comments = {"this is a comment", "another line"};
    vector<vector<int>> expected_codewords;
    expected_codewords.push_back({1, 2, 3, 4, 5, 6});
    expected_codewords.push_back({3, 7, 9});
    expected_codewords.push_back({8, 10, 11});
    expected_codewords.push_back({10, 12, 13});
    expected_codewords.push_back({3, 22, 24, 15});
    expected_codewords.push_back({21, 15, 13, 11});

    bool passing = puzzle.get_comments() == expected_comments;
    bool passing1 = puzzle.get_codewords() == expected_codewords;
    passing *= passing1;

    // more things to test

    return passing;
}
