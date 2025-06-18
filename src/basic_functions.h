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

bool are_letters_in_alphabet(std::string word, std::string alphabet);
bool does_word_match(std::string word, std::vector<int> codeword);


#endif