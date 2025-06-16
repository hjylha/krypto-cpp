#ifndef TEST_FUNCTIONS_H_INCLUDED
#define TEST_FUNCTIONS_H_INCLUDED

#include <string>
#include <map>
#include <vector>
#include "codewordpuzzle.h"
#include "file_operations.h"

using std::cout, std::endl, std::string, std::map, std::vector;

bool test_read_config(string test_default_filepath);
bool test_get_language_map(string test_language_file_path);

#endif