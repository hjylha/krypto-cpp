
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


bool test_get_minimum() {
    int num1 = 1;
    int num2 = 2;
    bool passing = get_minimum(num1, num2) == num1;

    num1 = 42;
    num2 = 28;
    bool passing1 = get_minimum(num1, num2) == num2;
    passing *= passing1;

    num1 = -1;
    num2 = -2;
    bool passing2 = get_minimum(num1, num2) == num2;
    passing *= passing2;

    num1 = -496;
    num2 = 0;
    bool passing3 = get_minimum(num1, num2) == num1;
    passing *= passing3;

    return passing;
}

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

bool test_add_whitespace2() {
    vector<string> text_vector = {"h", "e", "l", "l", "o"};
    int total_length = 7;
    string expected_text = "hello  ";
    bool passing = add_whitespace(text_vector, total_length) == expected_text;

    text_vector = {"ä", "l", "ä", "m", "ö", "l", "ö"};
    total_length = 10;
    expected_text = "älämölö   ";
    bool passing1 = add_whitespace(text_vector, total_length) == expected_text;
    passing *= passing1;

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

    text = "hello";
    expected_result = {"hello"};
    bool passing3 = split_string(text, delimiter) == expected_result;
    passing *= passing3;

    return passing;
}

bool test_utf8_split() {
    string text = "";
    bool passing = utf8_split(text).empty();

    text = "abcd";
    vector<string> expected_split = {"a", "b", "c", "d"};
    bool passing1 = utf8_split(text) == expected_split;
    passing *= passing1;

    text = "älämölö";
    expected_split = {"ä", "l", "ä", "m", "ö", "l", "ö"};
    bool passing2 = utf8_split(text) == expected_split;

    passing *= passing2;

    return passing;
}

bool test_join_string() {
    vector<string> text_vector;
    string expected_text = "";
    bool passing = join_string(text_vector, ",.?") == expected_text;

    text_vector = {"a", "b", "c", "d"};
    expected_text = "abcd";

    bool passing1 = join_string(text_vector, "") == expected_text;
    passing *= passing1;

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

bool test_lowercase_nonascii() {
    string text= "ÄO120 äo80";
    string expected_text = "äo120 äo80";
    bool passing = lowercase(text) == expected_text;

    text = "ÅÄÖ";
    expected_text = "åäö";
    bool passing1 = uppercase(text) == expected_text;
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

bool test_uppercase_nonascii() {
    string text= "ÄO120 äo80";
    string expected_text = "ÄO120 ÄO80";
    bool passing = uppercase(text) == expected_text;

    text = "åäö";
    expected_text = "ÅÄÖ";
    bool passing1 = uppercase(text) == expected_text;
    passing *= passing1;

    return passing;
}

bool test_find_string() {
    vector<string> text_vector = {"a", "b", "ö"};

    string text = "a";
    bool passing = find(text_vector, text) == 0;

    text = "ö";
    bool passing1 = find(text_vector, text) == 2;
    passing *= passing1;

    text = "c";
    bool passing2 = find(text_vector, text) == -1;

    return passing;
}

bool test_find_int() {
    vector<int> int_vector = {1, -1, 5, 0};

    int num = 1;
    bool passing = find(int_vector, num) == 0;

    num = -1;
    bool passing1 = find(int_vector, num) == 1;
    passing *= passing1;

    num = 2;
    bool passing2 = find(int_vector, num) == -1;
    passing *= passing2;

    num = 0;
    bool passing3 = find(int_vector, num) == 3;
    passing *= passing3;

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

bool test_get_alphabet_map() {
    string alphabet = "abc";
    map<string, int> expected_map;
    expected_map["a"] = 1;
    expected_map["b"] = 2;
    expected_map["c"] = 3;

    bool passing = get_alphabet_map(alphabet) == expected_map;

    alphabet = "åäö";
    map<string, int> expected_map2;
    expected_map2["å"] = 1;
    expected_map2["ä"] = 2;
    expected_map2["ö"] = 3;

    bool passing1 = get_alphabet_map(alphabet) == expected_map2;
    passing *= passing1;

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

    text = "öljytynnyri";
    bool passing5 = are_letters_in_alphabet(text, alphabet);
    passing *= passing5;
    // std::cout << text << " has " << text.length() << " letters" << std::endl;
    // std::cout << text[0] << " is the first letter of " << text << std::endl;
    // std::cout << alphabet[alphabet.length() - 1] << " is the last letter of " << alphabet << std::endl;
    // std::cout << alphabet << " has " << alphabet.length() << " letters" << std::endl;
    // std::cout << text.substr(0, 3) << " " << alphabet.substr(alphabet.length()- 3, 3) << std::endl;
    // for (int i = 1; i < text.length(); i++) {
    //     std::cout << text.substr(0, i) << " == " << "ö: " << (text.substr(0, i) == "ö") << std::endl; 
    // }

    return passing;
}

bool test_are_letters_in_alphabet2() {
    vector<string> text = {"a", "b", "c"};
    vector<string> alphabet = {"d", "e", "f"};
    bool passing = !are_letters_in_alphabet(text, alphabet);

    alphabet = {"a", "b", "c", "d", "e", "f", "g",
        "h", "i", "j", "k", "l", "m", "n",
        "o", "p", "q", "r", "s", "t", "u",
        "v", "w", "x", "y", "z"
    };
    text = alphabet;
    bool passing1 = are_letters_in_alphabet(text, alphabet);
    passing *= passing1;

    text = {"n", "o", "?"};
    bool passing2 = !are_letters_in_alphabet(text, alphabet);
    passing *= passing2;

    alphabet.push_back("?");
    text = {"y", "e", "s", "?"};
    bool passing3 = are_letters_in_alphabet(text, alphabet);
    passing *= passing3;

    alphabet.pop_back();
    alphabet.push_back("å");
    alphabet.push_back("ä");
    alphabet.push_back(("ö"));
    text = {"ä", "l", "ä", "m", "ö", "l", "ö"};
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

    word = "here";
    codeword = {3, 22, 24, 15};
    bool passing2 = !does_word_match(word, codeword);
    passing *= passing2;

    word = "öljytynnyri";
    codeword = {4,24,10,9,27,9,7,7,9,2,12};
    bool passing3 = does_word_match(word, codeword);
    passing *= passing3;

    return passing;
}

bool test_does_word_match2() {
    vector<string> word_vector = {"h", "e", "l", "l", "o"};
    vector<int> codeword = {1, 2, 3, 3, 4};
    bool passing = does_word_match(word_vector, codeword);

    word_vector = {"w", "o", "r", "l", "d"};
    codeword = {1, 2, 3, 4, 2};
    bool passing1 = !(does_word_match(word_vector, codeword));
    passing *= passing1;

    word_vector = {"h", "e", "r", "e"};
    codeword = {3, 22, 24, 15};
    bool passing2 = !does_word_match(word_vector, codeword);
    passing *= passing2;

    word_vector = {"ö", "l", "j", "y", "t", "y", "n", "n", "y", "r", "i"};
    codeword = {4,24,10,9,27,9,7,7,9,2,12};
    bool passing3 = does_word_match(word_vector, codeword);
    passing *= passing3;

    return passing;
}

bool test_does_int_word_match3() {
    vector<int> word_vector = {8, 5, 12, 12, 15};
    vector<int> codeword = {1, 2, 3, 3, 4};
    bool passing = does_int_word_match3(word_vector, codeword, 5);

    word_vector = {23, 15, 18, 12, 4};
    codeword = {1, 2, 3, 4, 2};
    bool passing1 = !(does_int_word_match3(word_vector, codeword, codeword.size()));
    passing *= passing1;

    word_vector = {8, 5, 18, 5};
    codeword = {3, 22, 24, 15};
    bool passing2 = !does_int_word_match3(word_vector, codeword, codeword.size());
    passing *= passing2;

    word_vector = {29, 12, 10, 25, 20, 25, 14, 14, 25, 18, 9};
    codeword = {4,24,10,9,27,9,7,7,9,2,12};
    bool passing3 = does_int_word_match3(word_vector, codeword, codeword.size());
    passing *= passing3;

    return passing;
}

bool test_get_matched_words() {
    vector<int> codeword = {1, 2, 3, 3, 4};
    vector<string> wordlist = {"hello", "world", "tiny", "english", "abccd", "öljytynnyri"};
    vector<string> expected_words = {"hello", "abccd"};
    bool passing = get_matched_words(codeword, wordlist, -1) == expected_words;

    codeword = {4,24,10,9,27,9,7,7,9,2,12};
    expected_words = {"öljytynnyri"};
    bool passing1 = get_matched_words(codeword, wordlist, -1) == expected_words;
    passing *= passing1;

    return passing;
}

bool test_get_matched_words2() {
    vector<int> codeword = {1, 2, 3, 3, 4};
    vector<vector<string>> wordlist = {
        {"h", "e", "l", "l", "o"},
        {"w", "o", "r", "l", "d"},
        {"t", "i", "n", "y"},
        {"e", "n", "g", "l", "i", "s", "h"},
        {"a", "b", "c", "c", "d"},
        {"ö", "l", "j", "y", "t", "y", "n", "n", "y", "r", "i"}
    };
    // vector<string> expected_words = {"hello", "abccd"};
    vector<vector<string>> expected_words = {{"h", "e", "l", "l", "o"}, {"a", "b", "c", "c", "d"}};
    bool passing = get_matched_words(codeword, wordlist, -1) == expected_words;

    codeword = {4,24,10,9,27,9,7,7,9,2,12};
    expected_words = {{"ö", "l", "j", "y", "t", "y", "n", "n", "y", "r", "i"}};
    bool passing1 = get_matched_words(codeword, wordlist, -1) == expected_words;
    passing *= passing1;

    return passing;
}

bool test_get_matched_words_int3() {
    vector<int> codeword = {1, 2, 3, 3, 4};
    vector<vector<int>> wordlist = {
        // {"h", "e", "l", "l", "o"},
        {8, 5, 12, 12, 15},
        // {"w", "o", "r", "l", "d"},
        {23, 15, 18, 12, 4},
        // {"t", "i", "n", "y"},
        {20, 9, 14, 25},
        // {"e", "n", "g", "l", "i", "s", "h"},
        {5, 14, 7, 12, 9, 19, 8},
        // {"a", "b", "c", "c", "d"},
        {1, 2, 3, 3, 4},
        // {"ö", "l", "j", "y", "t", "y", "n", "n", "y", "r", "i"}
        {29, 12, 10, 25, 20, 25, 14, 14, 25, 18, 9}
    };
    vector<int> word_lengths = {5, 5, 4, 7, 5, 11};
    // vector<string> expected_words = {"hello", "abccd"};
    vector<vector<int>> expected_words = {{8, 5, 12, 12, 15}, {1, 2, 3, 3, 4}};
    bool passing = get_matched_words_int3(codeword, 5, wordlist, word_lengths) == expected_words;

    codeword = {4,24,10,9,27,9,7,7,9,2,12};
    // expected_words = {"öljytynnyri"};
    expected_words = {{29, 12, 10, 25, 20, 25, 14, 14, 25, 18, 9}};
    bool passing1 = get_matched_words_int3(codeword, 11, wordlist, word_lengths) == expected_words;
    passing *= passing1;

    return passing;
}


bool test_does_path_exist() {

    string existing_file = "test_codewords.csv";
    bool passing = does_path_exist(existing_file);

    string non_existing_file = "file_does_not_exists_here.txt";
    bool passing1 = !does_path_exist(non_existing_file);
    passing *= passing1;

    string existing_test_file = "test_folder/test.csv";
    bool passing2 = does_path_exist(existing_test_file);
    passing *= passing2;

    return passing;
}

bool test_does_path_exist_folder_edition() {
    string current_work_directory = std::filesystem::current_path().string();
    bool passing = does_path_exist(current_work_directory);

    string existing_directory = "test_folder/";
    bool passing1 = does_path_exist(existing_directory);
    passing *= passing1;

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
    bool passing2 = config[lang1]["alphabet"] == "abcdefghijklmnopqrstuvwxyzåäö";
    bool passing3 = config[lang1]["wordlist_path"] == "test_stuff/test_wordlist";
    bool passing4 = config[lang1]["codeword_folder_path"] == "test_stuff";
    passing = passing && passing1 && passing2 && passing3 && passing4;

    bool passing5 = config[lang2]["name"] == "second";
    bool passing6 = config[lang2]["alphabet"] == "abcdefg";
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
    vector<string> expected_wordlist = {
        "some",
        "words",
        "here",
        "to",
        "be",
        "read",
        "by",
        "someone",
        "or",
        "something",
        "cola",
        "camp",
        "öljytynnyri"};

    bool passing = wordlist == expected_wordlist;

    return passing;
}

bool test_get_wordlist_vector(string test_wordlist_path) {
    vector<vector<string>> wordlist = get_wordlist_vector(test_wordlist_path);
    vector<vector<string>> expected_wordlist = {
        {"s", "o", "m", "e"},
        {"w", "o", "r", "d", "s"},
        {"h", "e", "r", "e"},
        {"t", "o"},
        {"b", "e"},
        {"r", "e", "a", "d"},
        {"b", "y"},
        {"s", "o", "m", "e", "o", "n", "e"},
        {"o", "r"},
        {"s", "o", "m", "e", "t", "h", "i", "n", "g"},
        {"c", "o", "l", "a"},
        {"c", "a", "m", "p"},
        {"ö", "l", "j", "y", "t", "y", "n", "n", "y", "r", "i"}
    };
    bool passing = wordlist == expected_wordlist;
    return passing;
}

bool test_get_wordlist_as_int_vector(string test_wordlist_path) {
    vector<vector<int>> wordlist = get_wordlist_as_int_vector(test_wordlist_path);
    vector<vector<int>> expected_wordlist = {
        {1, 2, 3, 4},
        {5, 2, 6, 7, 1},
        {8, 4, 6, 4},
        {9, 2},
        {10, 4},
        {6, 4, 11, 7},
        {10, 12},
        {1, 2, 3, 4, 2, 13, 4},
        {2, 6},
        {1, 2, 3, 4, 9, 8, 14, 13, 15},
        {16, 2, 17, 11},
        {16, 11, 3, 18},
        {19, 17, 20, 12, 9, 12, 13, 13, 12, 6, 14}
    };
    bool passing = wordlist.size() == expected_wordlist.size();

    bool passing1 = wordlist == expected_wordlist;
    passing *= passing1;

    for (int i = 0; i < wordlist.size(); i++) {
        if (wordlist[i] != expected_wordlist[i]) {
            for (int num : wordlist[i]) {
                std::cout << num << "  ";
            }
            std::cout << std::endl;
        }
    }
    return passing;   
}

bool test_get_wordlist_as_int_vector_plus(string test_wordlist_path) {
    string alphabet = "abcdefghijklmnopqrstuvwxyzåäö";
    map<string, int> alphabet_map = get_alphabet_map(alphabet);

    vector<int> expected_lengths = {4, 5, 4, 2, 2, 4, 2, 7, 2, 9, 4, 4, 11};

    vector<vector<int>> expected_wordlist = {
        {19, 15, 13, 5},
        {23, 15, 18, 4, 19},
        {8, 5, 18, 5},
        {20, 15},
        {2, 5},
        {18, 5, 1, 4},
        {2, 25},
        {19, 15, 13, 5, 15, 14, 5},
        {15, 18},
        {19, 15, 13, 5, 20, 8, 9, 14, 7},
        {3, 15, 12, 1},
        {3, 1, 13, 16},
        {29, 12, 10, 25, 20, 25, 14, 14, 25, 18, 9}
    };

    pair<vector<int>, vector<vector<int>>> words_and_lengths = get_wordlist_as_int_vector_plus(test_wordlist_path, alphabet_map);

    vector<int> word_lengths = words_and_lengths.first;
    vector<vector<int>> wordlist = words_and_lengths.second;

    bool passing = word_lengths.size() == wordlist.size();

    bool passing1 = word_lengths == expected_lengths;
    passing *= passing1;

    bool passing2 = wordlist == expected_wordlist;
    passing *= passing2;
    // for (int i = 0; i < word_lengths.size(); i++) {
    //     if (expected_wordlist[i] != wordlist[i]) {
    //         std::cout << "expected:" << std::endl;
    //         for (int num : expected_wordlist[i]) {
    //             std::cout << num << " ";
    //         }
    //         std::cout << "\n" << "actual:" << std::endl;
    //         for (int num : wordlist[i]) {
    //             std::cout << num << " ";
    //         }
    //     }
    // }

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
    expected_codewords.push_back({4,24,10,9,27,9,7,7,9,2,12});

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

bool test_get_codewords_and_comments(string test_codeword_path) {
    vector<string> expected_comments = {"this is a comment", "another line"};
    vector<vector<int>> expected_codewords;
    expected_codewords.push_back({1, 2, 3, 4, 5, 6});
    expected_codewords.push_back({3, 7, 9});
    expected_codewords.push_back({8, 10, 11});
    expected_codewords.push_back({10, 12, 13});
    expected_codewords.push_back({3, 22, 24, 15});
    expected_codewords.push_back({21, 15, 13, 11});
    expected_codewords.push_back({4,24,10,9,27,9,7,7,9,2,12});
    vector<int> expected_lengths = {6, 3, 3, 3, 4, 4, 11};

    CodewordsAndComments c_n_c = get_codewords_and_comments(test_codeword_path);

    bool passing = c_n_c.comments == expected_comments;

    bool passing1 = c_n_c.codewords == expected_codewords;
    passing *= passing1;

    bool passing2 = c_n_c.codeword_lengths == expected_lengths;
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

    codeword1 = {3, 22, 24, 15};
    codeword2 = {21, 15, 13, 11};
    exp_match_ind_n_othr = MatchingIndicesAndOthers({pair<int, int>(3, 1)}, {0, 1, 2}, {0, 2, 3});
    bool passing3 = exp_match_ind_n_othr == get_matching_indices(codeword1, codeword2);
    passing *= passing3;

    return passing;
}

bool test_do_words_match_to_matching_indices() {
    // string word1 = "hello";
    // string word2 = "live";
    vector<string> word1 = {"h", "e", "l", "l", "o"};
    vector<string> word2 = {"l", "i", "v", "e"};
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
    // string word1 = "";
    // string word2 = "";
    vector<string> word1, word2;
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
    expected_codewords.push_back({4,24,10,9,27,9,7,7,9,2,12});

    bool passing = puzzle.get_comments() == expected_comments;
    bool passing1 = puzzle.get_codewords() == expected_codewords;
    passing *= passing1;
    // more things to test

    // vector<vector<string>> expected_matches = {{}, {}, {}, {}, {"some", "read", "cola", "camp"}, {"some", "read", "cola", "camp"}};
    vector<vector<vector<string>>> expected_matches = {
        {},
        {},
        {},
        {},
        {{"s", "o", "m", "e"}, {"r", "e", "a", "d"}, {"c", "o", "l", "a"}, {"c", "a", "m", "p"}},
        {{"s", "o", "m", "e"}, {"r", "e", "a", "d"}, {"c", "o", "l", "a"}, {"c", "a", "m", "p"}},
        {{"ö", "l", "j", "y", "t", "y", "n", "n", "y", "r", "i"}}
    };
    bool passing2 = true;
    vector<int> codeword;
    // vector<string> m_words;
    vector<vector<string>> m_words;
    for (int i = 0; i < expected_matches.size(); i++) {
        m_words = puzzle.get_matched_words_for_codeword(i);
        passing2 = m_words == expected_matches[i];
        passing *= passing2;
        // if (!passing2) {
        //     vector<int> codeword = puzzle.get_codewords()[i];
        //     std::cout << "codeword" << std::endl;
        //     for (int j = 0; j < codeword.size(); j++) {
        //         std::cout << codeword[j] << "  ";
        //     }
        //     std::cout << std::endl << "matched words" << std::endl;
        //     for (string word : m_words) {
        //         std::cout << word << ", ";
        //     }
        //     std::cout << std::endl << "expected words" << std::endl;
        //     for (string word : expected_matches[i]) {
        //         std::cout << word << ", ";
        //     }
        //     std::cout << std::endl;
            
        // }
    }
    // passing *= passing2;

    return passing;
}

bool test_substitution_vector_things(CodewordPuzzle puzzle) {
    bool passing = puzzle.get_letters_in_substitution_vector().empty();

    int the_number = 1;
    // char the_letter = 'b';
    string the_letter = "b";
    int result = puzzle.add_to_substitution_vector(the_number, the_letter, std::map<string, int>(), false);
    vector<string> expected_chars;
    expected_chars.push_back(the_letter);
    bool passing1 = puzzle.get_letters_in_substitution_vector() == expected_chars;
    passing *= passing1;

    bool passing2 = puzzle.count_solved_numbers() == 1;
    passing *= passing2;

    puzzle.clear_substitution_vector();
    bool passing3 = puzzle.count_solved_numbers() == 0;
    passing *= passing3;

    the_letter = "ö";
    expected_chars.clear();
    expected_chars.push_back(the_letter);
    result = puzzle.add_to_substitution_vector(the_number, the_letter, std::map<string, int>(), false);
    bool passing4 = puzzle.get_letters_in_substitution_vector() == expected_chars;

    puzzle.clear_substitution_vector();

    return passing;
}

bool test_sort_codewords(CodewordPuzzle puzzle) {
    vector<int> expected_indices = {6, 4, 5};
    bool passing = puzzle.sort_codewords() == expected_indices;
    return passing;
}

bool test_match_two_codewords(CodewordPuzzle puzzle) {
    // vector<int> codeword1 = {3, 22, 24, 15};
    // vector<int> codeword2 = {21, 15, 13, 11};
    int codeword_index1 = 4;
    int codeword_index2 = 5;

    // std::vector<std::pair<std::string, std::string>> matching_pairs = puzzle.match_two_codewords(codeword1, codeword2, 999);
    std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>> matching_pairs = puzzle.match_two_codewords(codeword_index1, codeword_index2, 999);

    bool passing = matching_pairs.size() == 1;
    // std::cout << "Found " << matching_pairs.size() << " pairs" << std::endl;

    // bool passing1 = matching_pairs[0].first == "some";
    bool passing1 = join_string(matching_pairs[0].first, "") == "some";
    passing *= passing1;

    // bool passing2 = matching_pairs[0].second == "read";
    bool passing2 = join_string(matching_pairs[0].second, "") == "read";
    passing *= passing2;

    // matching_pairs = puzzle.match_two_codewords(codeword_index1, codeword_index2, 999);
    // passing *= matching_pairs.size() == 1;

    // passing1 = matching_pairs[0].first == "some";
    // passing *= passing1;

    // passing2 = matching_pairs[0].second == "read";
    // passing *= passing2;

    return passing;
}

bool test_find_all_unique_pairs(CodewordPuzzle puzzle) {
    vector<CodewordWordPair> unique_pairs = puzzle.find_all_unique_pairs();

    // (3, 22, 24, 15) - (21, 15, 13, 11) = some - read
    // (3, 24, 24, 15) - (4,24,10,9,27,9,7,7,9,2,12) = cola - öljytynnyri
    // others?

    bool passing = unique_pairs.size() == 2;

    // for (auto p : unique_pairs) {
    //     std::cout << "pair" << std::endl;
    //     std::cout << codeword_as_str(p.codeword1) << "  " << codeword_as_str(p.codeword2) << std::endl;
    //     std::cout << join_string(p.word1, "") << "  " << join_string(p.word2, "")  << std::endl;
    // }

    // MORE TO COME

    return passing;
}


bool test_do_words_match_to_matching_indices_int() {
    // vector<string> word1 = {"h", "e", "l", "l", "o"};
    // vector<string> word2 = {"l", "i", "v", "e"};
    vector<int> word1 = {8, 5, 12, 12, 15};
    vector<int> word2 = {12, 9, 22, 5};
    vector<pair<int, int>> matching_indices = {pair<int, int>(1, 3), pair<int, int>(2, 0)};
    vector<int> indices_in_word1 = {0, 4};
    vector<int> indices_in_word2 = {1, 2};
    MatchingIndicesAndOthers match_ind_n_othr(matching_indices, indices_in_word1, indices_in_word2);
    bool passing = do_words_match_to_matching_indices(word1, word2, match_ind_n_othr);
    return passing;
}

bool test_CodewordWordPair1() {
    vector<int> codeword1, codeword2;
    vector<int> word1, word2;
    CodewordWordPair1 cw_w_pair = CodewordWordPair1(codeword1, codeword2, word1, word2);

    bool passing = cw_w_pair.codeword1 == codeword1;
    bool passing1 = cw_w_pair.codeword2 == codeword2;
    passing *= passing1;

    bool passing2 = cw_w_pair.word1 == word1;
    passing *= passing2;
    bool passing3 = cw_w_pair.word2 == word2;
    passing *= passing3;

    return passing;
}

bool test_CodewordPuzzle1(CodewordPuzzle1 puzzle) {
    vector<string> expected_comments = {"this is a comment", "another line"};
    vector<vector<int>> expected_codewords;
    expected_codewords.push_back({1, 2, 3, 4, 5, 6});
    expected_codewords.push_back({3, 7, 9});
    expected_codewords.push_back({8, 10, 11});
    expected_codewords.push_back({10, 12, 13});
    expected_codewords.push_back({3, 22, 24, 15});
    expected_codewords.push_back({21, 15, 13, 11});
    expected_codewords.push_back({4,24,10,9,27,9,7,7,9,2,12});

    bool passing = puzzle.get_comments() == expected_comments;
    bool passing1 = puzzle.get_codewords() == expected_codewords;
    passing *= passing1;
    // more things to test

    // vector<vector<string>> expected_matches = {{}, {}, {}, {}, {"some", "read", "cola", "camp"}, {"some", "read", "cola", "camp"}};
    vector<vector<vector<int>>> expected_matches = {
        {},
        {},
        {},
        {},
        {{19, 15, 13, 5}, {18, 5, 1, 4}, {3, 15, 12, 1}, {3, 1, 13, 16}},
        {{19, 15, 13, 5}, {18, 5, 1, 4}, {3, 15, 12, 1}, {3, 1, 13, 16}},
        {{29, 12, 10, 25, 20, 25, 14, 14, 25, 18, 9}}
    };
    bool passing2 = true;
    vector<int> codeword;
    // vector<string> m_words;
    vector<vector<int>> m_words;
    for (int i = 0; i < expected_matches.size(); i++) {
        m_words = puzzle.get_matched_words_for_codeword(i);
        passing2 = m_words == expected_matches[i];
        passing *= passing2;
        // if (!passing2) {
        //     vector<int> codeword = puzzle.get_codewords()[i];
        //     std::cout << "codeword" << std::endl;
        //     for (int j = 0; j < codeword.size(); j++) {
        //         std::cout << codeword[j] << "  ";
        //     }
        //     std::cout << std::endl << "matched words" << std::endl;
        //     for (string word : m_words) {
        //         std::cout << word << ", ";
        //     }
        //     std::cout << std::endl << "expected words" << std::endl;
        //     for (string word : expected_matches[i]) {
        //         std::cout << word << ", ";
        //     }
        //     std::cout << std::endl;
            
        // }
    }
    // passing *= passing2;

    return passing;
}

bool test_substitution_vector_things1(CodewordPuzzle1 puzzle) {
    bool passing = true;
    for (int num : puzzle.get_substitution_vector()) {
        if (num != 0) {
            passing = false;
        }
    }

    int the_number = 1;
    // char the_letter = 'b';
    // string the_letter = "b";
    int the_letter = 2;
    int result = puzzle.add_to_substitution_vector(the_number, the_letter, std::map<string, int>(), false);
    // vector<int> expected_chars;
    // expected_chars.push_back(the_letter);
    bool passing1 = puzzle.get_substitution_vector()[the_number] == the_letter;
    passing *= passing1;
    bool passing1_2 = puzzle.get_substitution_vector_opp()[the_letter] == the_number;
    passing *= passing1_2;

    bool passing2 = puzzle.count_solved_numbers() == 1;
    passing *= passing2;

    puzzle.clear_substitution_vector();
    bool passing3 = puzzle.count_solved_numbers() == 0;
    passing *= passing3;

    // the_letter = "ö";
    the_letter = 29;
    // expected_chars.clear();
    // expected_chars.push_back(the_letter);
    result = puzzle.add_to_substitution_vector(the_number, the_letter, std::map<string, int>(), false);
    bool passing4 = puzzle.get_substitution_vector()[the_number] == the_letter;
    passing *= passing4;
    bool passing4_2 = puzzle.get_substitution_vector_opp()[the_letter] == the_number;
    passing *= passing4_2;

    puzzle.clear_substitution_vector();

    return passing;
}

bool test_sort_codewords1(CodewordPuzzle1 puzzle) {
    vector<int> expected_indices = {6, 4, 5};
    bool passing = puzzle.sort_codewords() == expected_indices;
    return passing;
}

bool test_match_two_codewords1(CodewordPuzzle1 puzzle) {
    // vector<int> codeword1 = {3, 22, 24, 15};
    // vector<int> codeword2 = {21, 15, 13, 11};
    int codeword_index1 = 4;
    int codeword_index2 = 5;

    // std::vector<std::pair<std::string, std::string>> matching_pairs = puzzle.match_two_codewords(codeword1, codeword2, 999);
    std::vector<std::pair<std::vector<int>, std::vector<int>>> matching_pairs = puzzle.match_two_codewords(codeword_index1, codeword_index2, 999);

    bool passing = matching_pairs.size() == 1;
    // std::cout << "Found " << matching_pairs.size() << " pairs" << std::endl;

    // bool passing1 = matching_pairs[0].first == "some";
    vector<int> expected1 = {19, 15, 13, 5};
    bool passing1 = matching_pairs[0].first == expected1;
    // bool passing1 = join_string(matching_pairs[0].first, "") == "some";
    passing *= passing1;

    // bool passing2 = matching_pairs[0].second == "read";
    vector<int> expected2 = {18, 5, 1, 4};
    bool passing2 = matching_pairs[0].second == expected2;
    // bool passing2 = join_string(matching_pairs[0].second, "") == "read";
    passing *= passing2;

    // matching_pairs = puzzle.match_two_codewords(codeword_index1, codeword_index2, 999);
    // passing *= matching_pairs.size() == 1;

    // passing1 = matching_pairs[0].first == "some";
    // passing *= passing1;

    // passing2 = matching_pairs[0].second == "read";
    // passing *= passing2;

    return passing;
}

bool test_find_all_unique_pairs1(CodewordPuzzle1 puzzle) {
    vector<CodewordWordPair1> unique_pairs = puzzle.find_all_unique_pairs();

    // (3, 22, 24, 15) - (21, 15, 13, 11) = some - read
    // (3, 24, 24, 15) - (4,24,10,9,27,9,7,7,9,2,12) = cola - öljytynnyri
    // others?

    bool passing = unique_pairs.size() == 2;

    // for (auto p : unique_pairs) {
    //     std::cout << "pair" << std::endl;
    //     std::cout << codeword_as_str(p.codeword1) << "  " << codeword_as_str(p.codeword2) << std::endl;
    //     std::cout << join_string(p.word1, "") << "  " << join_string(p.word2, "")  << std::endl;
    // }

    // MORE TO COME

    return passing;
}

