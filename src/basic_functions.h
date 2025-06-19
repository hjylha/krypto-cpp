#ifndef BASIC_FUNCTIONS_H_INCLUDED
#define BASIC_FUNCTIONS_H_INCLUDED

#include <map>
#include <vector>
#include <string>
#include <iostream>


std::string remove_whitespace(std::string);
std::string add_whitespace(std::string, int total_length);
std::vector<std::string> split_string(std::string text, char delimiter);
std::string lowercase(std::string text);
std::string uppercase(std::string text);

std::string codeword_as_str(std::vector<int> codeword);
std::string mass_replace(std::string text, std::vector<std::string> replacements);
std::vector<int> get_nums_in_codewords(std::vector<std::vector<int>> codewords);

bool are_letters_in_alphabet(std::string word, std::string alphabet);
bool does_word_match(std::string word, std::vector<int> codeword);
std::vector<std::string> get_matched_words(std::vector<int> codeword, std::vector<std::string> wordlist, int maximum_matches);


#endif