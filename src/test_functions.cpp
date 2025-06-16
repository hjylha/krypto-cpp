
#include <string>
#include <map>
#include <vector>
#include "codewordpuzzle.h"

using std::cout, std::endl, std::string, std::map, std::vector;

bool test_read_config(string test_default_filepath)
{
    map<string, map<string, string>> config = read_config(test_default_filepath);
    // string default_language;

    bool passing = true;

    string lang1 = "tag";
    string lang2 = "another_tag";
    bool passing1 = config[lang1]["name"] == "default";
    bool passing2 = config[lang1]["alphabet"] == "abcdefg";
    bool passing3 = config[lang1]["wordlist_path"] == "test_stuff/test_wordlist";
    bool passing4 = config[lang1]["codeword_folder_path"] == "test_stuff";
    passing = passing && passing1 && passing2 && passing3 && passing4;

    bool passing5 = config[lang2]["name"] == "second";
    bool passing6 = config[lang2]["alphabet"] == "abcdefghijklmnopqrstuvwxyzåäö";
    bool passing7 = config[lang2]["wordlist_path"] == "";
    bool passing8 = config[lang2]["codeword_folder_path"] == "";
    passing = passing && passing5 && passing6 && passing7 && passing8;
    return passing;
}


bool test_get_language_map(string test_language_file_path)
{
    map<string, string> language_map = get_language_map(test_language_file_path);
    return false;
}