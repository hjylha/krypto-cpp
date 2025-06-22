#ifndef TEST_FUNCTIONS_H_INCLUDED
#define TEST_FUNCTIONS_H_INCLUDED

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "basic_functions.h"
#include "file_operations.h"
#include "codewordpuzzle.h"

using std::cout, std::endl, std::string, std::map, std::vector, std::pair;

// basic_functions
bool test_remove_whitespace();
bool test_add_whitespace();
bool test_split_string();
bool test_lowercase();
bool test_uppercase();
bool test_codeword_as_str();
bool test_mass_replace();
bool test_get_nums_in_codewords();
bool test_are_letters_in_alphabet();
bool test_does_word_match();
bool test_get_matched_words();

// file_operations
bool test_read_config(string test_default_filepath);
bool test_get_language_map(string test_language_file_path);
bool test_get_wordlist(string test_wordlist_path);
bool test_get_codewords(string test_codeword_path);

// CodewordPuzzle
bool test_get_matching_indices();
bool test_do_words_match_to_matching_indices();
bool test_CodewordWordPair();
bool test_CodewordPuzzle(CodewordPuzzle puzzle);

#endif