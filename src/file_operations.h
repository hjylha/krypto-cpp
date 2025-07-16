#ifndef FILE_OPERATIONS_H_INCLUDED
#define FILE_OPERATIONS_H_INCLUDED

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "basic_functions.h"


bool does_path_exist(std::string path);
std::map<std::string, std::map<std::string, std::string>> get_language_map(const std::string& filepath);
std::map<std::string, std::map<std::string, std::string>> read_config(const std::string& filepath);
std::vector<std::string> get_wordlist(const std::string& filepath);
std::vector<std::vector<std::string>> get_wordlist_vector(const std::string& filepath);
std::vector<std::vector<int>> get_wordlist_as_int_vector(const std::string& filepath);
std::pair<std::vector<int>, std::vector<std::vector<int>>> get_wordlist_as_int_vector_plus(const std::string& filepath, std::map<std::string, int> alphabet_map);
std::vector<std::vector<int>> get_wordlist_int(const std::string& filepath);
std::pair<std::vector<std::string>, std::vector<std::vector<int>>> get_codewords(const std::string& filepath);
// std::vector<std::vector<int>> readCSVIntegers(const std::string& filepath);
std::vector<std::string> get_csv_files_in_folder(std::string folder_path);


struct CodewordsAndComments
{
private:

public:
    std::vector<std::string> comments;
    std::vector<int> codeword_lengths;
    std::vector<std::vector<int>> codewords;

    CodewordsAndComments();
    CodewordsAndComments(std::vector<std::string> the_comments, std::vector<int> the_codeword_lengths, std::vector<std::vector<int>> the_codewords);
};

CodewordsAndComments get_codewords_and_comments(const std::string& filepath);

#endif