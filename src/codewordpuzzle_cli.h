#ifndef CODEWORDPUZZLE_CLI_H_INCLUDED
#define CODEWORDPUZZLE_CLI_H_INCLUDED


#include <map>
#include <string>
#include <utility>
#include <vector>
#include <chrono>
#include "codewordpuzzle.h"


bool yes_or_no_question(std::string question_text, std::pair<char, char> yes_no_pair, std::string help_text);


class PuzzleCLI
{
private:
    std::string DEFAULT_LANGUAGE_FILE_PATH = "language_file.csv";
    std::string DEFAULT_CONFIG_PATH = "krypto.cfg";
    std::string NAME_KEY = "name";
    std::string ALPHABET_KEY = "alphabet";
    std::string ALPHABET_UPPER_KEY = "alphabet_upper";
    std::string WORDLIST_PATH_KEY = "wordlist_path";
    std::string CODEWORD_FOLDER_PATH_KEY = "codeword_folder_path";

    double SOLUTION_SUCCESS_THRESHOLD = 0.75;

    char solved_char = '*';

    std::map<std::string, int> issues;

    std::string default_language, language;
    std::map<std::string, std::map<std::string, std::string>> language_map, config;
    std::map<std::string, std::string> current_language_map;
    std::string wordlist_path, codeword_path;

    std::vector<std::string> alphabet;
    std::vector<std::string> alphabet_upper;

    CodewordPuzzle puzzle;
    
public:
    bool running = true;
    PuzzleCLI();
    ~PuzzleCLI();
    // A function pointer to member functions
    typedef void (PuzzleCLI::*MemberFuncPtr)();
    // void CallSelectedFunction(MemberFuncPtr func);
    std::pair<char, char> get_yes_no_pair();
    bool yes_no_question(std::string question_text);
    std::string to_upper(std::string text);
    std::string to_lower(std::string text);
    std::string to_upper(std::vector<std::string> text_vector);
    std::string to_lower(std::vector<std::string> text_vector);
    void set_language(std::string new_language);
    std::vector<std::string> get_languages();
    void choose_language();
    int choose_codeword_path();
    void initialize_puzzle(std::string the_codeword_path, std::string the_wordlist_path);
    void input_data_and_initialize_puzzle(std::string the_language, std::string the_codeword_path);
    void restart();
    void exit_program();
    void add_to_substitution_vector();
    void set_codeword_as_word();
    void print_pairs(CodewordWordPair codeword_word_pair);
    // std::vector<CodewordWordPair> find_unique_pairs();
    void find_unique_pairs();
    void print_solving_stats(double elapsed_time);
    void try_to_solve_puzzle_fully_methodically();
    void try_to_solve_puzzle_methodically(std::chrono::time_point<std::chrono::high_resolution_clock> start_time);
    void try_to_solve_puzzle_with_steps();
    void print_substitution_vector();
    void print_initial_info();
    void print_missing_chars();
    void print_codeword_progress();
    void print_codeword_progress(std::vector<std::vector<int>> codewords_here);
    void choose_progress_to_show();
    void show_matching_words();
    void choose_main_choice();
};


class PuzzleCLI1
{
private:
    std::string DEFAULT_LANGUAGE_FILE_PATH = "language_file.csv";
    std::string DEFAULT_CONFIG_PATH = "krypto.cfg";
    std::string NAME_KEY = "name";
    std::string ALPHABET_KEY = "alphabet";
    std::string ALPHABET_UPPER_KEY = "alphabet_upper";
    std::string WORDLIST_PATH_KEY = "wordlist_path";
    std::string CODEWORD_FOLDER_PATH_KEY = "codeword_folder_path";

    double SOLUTION_SUCCESS_THRESHOLD = 0.75;

    char solved_char = '*';
    std::string empty_symbol = "_";

    std::map<std::string, int> issues;

    std::string default_language, language;
    std::map<std::string, std::map<std::string, std::string>> language_map, config;
    std::map<std::string, std::string> current_language_map;
    std::string wordlist_path, codeword_path;

    std::vector<std::string> alphabet;
    std::vector<std::string> alphabet_upper;
    std::map<std::string, int> alphabet_map;

    CodewordPuzzle1 puzzle;
    
public:
    bool running = true;
    PuzzleCLI1();
    ~PuzzleCLI1();
    // A function pointer to member functions
    typedef void (PuzzleCLI1::*MemberFuncPtr)();
    // void CallSelectedFunction(MemberFuncPtr func);
    std::pair<char, char> get_yes_no_pair();
    bool yes_no_question(std::string question_text);
    std::string to_upper(std::string text);
    std::string to_lower(std::string text);
    std::string to_upper(std::vector<std::string> text_vector);
    std::string to_lower(std::vector<std::string> text_vector);
    std::string to_upper_int(std::vector<int> text_vector);
    std::string to_lower_int(std::vector<int> text_vector);
    std::string replace1(std::string text_key, std::string replacement_text);
    std::string replace2(std::string text_key, std::string replacement_text1, std::string replacement_text2);
    std::string replace3(std::string text_key, std::string replacement_text1, std::string replacement_text2, std::string replacement_text3);
    void set_language(std::string new_language);
    std::vector<std::string> get_languages();
    void choose_language();
    int choose_codeword_path();
    void initialize_puzzle(std::string the_codeword_path, std::string the_wordlist_path);
    void input_data_and_initialize_puzzle(std::string the_language, std::string the_codeword_path);
    void restart();
    void exit_program();
    std::pair<std::vector<int>, std::vector<int>> ask_for_numbers_and_letters();
    void add_to_substitution_vector();
    void set_codeword_as_word();
    void print_pairs(CodewordWordPair1 codeword_word_pair);
    // std::vector<CodewordWordPair> find_unique_pairs();
    void find_unique_pairs();
    void print_solving_stats(double elapsed_time);
    void try_to_solve_puzzle_fully_methodically();
    void try_to_solve_puzzle_methodically(std::chrono::time_point<std::chrono::high_resolution_clock> start_time);
    void try_to_solve_puzzle_with_steps();
    void print_substitution_vector();
    void print_initial_info();
    void print_missing_chars();
    void print_codeword_progress();
    void print_codeword_progress(std::vector<std::vector<int>> codewords_here);
    void choose_progress_to_show();
    void show_matching_words();
    void choose_main_choice();
};


#endif
