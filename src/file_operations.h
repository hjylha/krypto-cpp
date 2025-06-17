#ifndef FILE_OPERATIONS_H_INCLUDED
#define FILE_OPERATIONS_H_INCLUDED

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "basic_functions.h"


std::map<std::string, std::map<std::string, std::string>> get_language_map(const std::string& filepath);
std::map<std::string, std::map<std::string, std::string>> read_config(const std::string& filepath);
std::vector<std::vector<int>> readCSVIntegers(const std::string& filepath);

#endif