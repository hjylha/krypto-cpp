#ifndef BASIC_FUNCTIONS_H_INCLUDED
#define BASIC_FUNCTIONS_H_INCLUDED

#include <map>
#include <vector>
#include <string>


int get_minimum(int num1, int num2);
std::string remove_whitespace(std::string text);
std::string add_whitespace(std::string text, int total_length);
std::string add_whitespace(std::vector<std::string> text_vector, int total_length);
std::vector<std::string> split_string(std::string text, char delimiter);
std::vector<std::string> utf8_split(const std::string& text);
std::string join_string(std::vector<std::string> text_vector, std::string delimiter);
std::string lowercase(std::string text);
std::string uppercase(std::string text);
int find(std::vector<std::string> text_vector, std::string text);
int find(std::vector<int> int_vector, int num);

std::string codeword_as_str(std::vector<int> codeword);
std::string mass_replace(std::string text, std::vector<std::string> replacements);
std::vector<int> get_nums_in_codewords(std::vector<std::vector<int>> codewords);

bool are_letters_in_alphabet(std::string word, std::string alphabet);
bool are_letters_in_alphabet(std::vector<std::string> word_vector, std::vector<std::string> alphabet);
bool does_word_match(std::string word, std::vector<int> codeword);
bool does_word_match(std::vector<std::string> word_vector, std::vector<int> codeword);
bool does_word_match(std::vector<std::string> word_vector, std::vector<int> codeword, int word_length, int codeword_length);
bool does_int_word_match(std::vector<int> int_vector, std::vector<int> codeword);
bool does_int_word_match2(std::vector<int> int_vector, std::vector<int> codeword);
std::vector<std::string> get_matched_words(std::vector<int> codeword, std::vector<std::string> wordlist, int maximum_matches);
std::vector<std::vector<std::string>> get_matched_words(std::vector<int> codeword, std::vector<std::vector<std::string>> wordlist, int maximum_matches);
std::vector<std::vector<std::string>> get_matched_words2(std::vector<int> codeword, std::vector<std::vector<std::string>> wordlist, int maximum_matches);
std::vector<std::vector<std::string>> get_matched_words3(std::vector<int> codeword, int codeword_length, std::vector<std::vector<std::string>> wordlist, std::vector<int> word_lengths);
std::vector<std::vector<int>> get_matched_words_int(std::vector<int> codeword, std::vector<std::vector<int>> wordlist_int, int maximum_matches);
std::vector<std::vector<int>> get_matched_words_int2(std::vector<int> codeword, std::vector<std::vector<int>> wordlist_int);


#endif