#ifndef TEST_FUNCTIONS_H_INCLUDED
#define TEST_FUNCTIONS_H_INCLUDED

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "basic_functions.h"
#include "file_operations.h"
#include "codewordpuzzle.h"

using std::string, std::map, std::vector, std::pair;

// basic_functions
bool test_get_minimum();
bool test_remove_whitespace();
bool test_add_whitespace();
bool test_add_whitespace2();
bool test_split_string();
bool test_utf8_split();
bool test_join_string();
bool test_lowercase();
bool test_lowercase_nonascii();
bool test_uppercase();
bool test_uppercase_nonascii();
bool test_find_string();
bool test_find_int();
bool test_codeword_as_str();
bool test_get_alphabet_map();
bool test_mass_replace();
bool test_get_nums_in_codewords();
bool test_are_letters_in_alphabet();
bool test_are_letters_in_alphabet2();
bool test_does_word_match();
bool test_does_word_match2();
bool test_get_matched_words();
bool test_get_matched_words2();

// file_operations
bool test_does_path_exist();
bool test_does_path_exist_folder_edition();
bool test_read_config(string test_default_filepath);
bool test_get_language_map(string test_language_file_path);
bool test_get_wordlist(string test_wordlist_path);
bool test_get_wordlist_vector(string test_wordlist_path);
bool test_get_wordlist_as_int_vector(string test_wordlist_path);
bool test_get_wordlist_as_int_vector_plus(string test_wordlist_path);
bool test_get_codewords(string test_codeword_path);
bool test_get_csv_files_in_folder();
bool test_get_codewords_and_comments(string test_codeword_path);

// CodewordPuzzle
bool test_get_matching_indices();
bool test_do_words_match_to_matching_indices();
bool test_CodewordWordPair();
bool test_CodewordPuzzle(CodewordPuzzle puzzle);
bool test_substitution_vector_things(CodewordPuzzle puzzle);
bool test_sort_codewords(CodewordPuzzle puzzle);
bool test_match_two_codewords(CodewordPuzzle puzzle);
bool test_find_all_unique_pairs(CodewordPuzzle puzzle);

// CodewordPuzzle1
bool test_do_words_match_to_matching_indices_int();
bool test_CodewordWordPair1();
bool test_CodewordPuzzle1(CodewordPuzzle1 puzzle);
bool test_substitution_vector_things1(CodewordPuzzle1 puzzle);

#endif