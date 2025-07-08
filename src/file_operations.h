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
std::pair<std::vector<std::string>, std::vector<std::vector<int>>> get_codewords(const std::string& filepath);
// std::vector<std::vector<int>> readCSVIntegers(const std::string& filepath);
std::vector<std::string> get_csv_files_in_folder(std::string folder_path);

#endif