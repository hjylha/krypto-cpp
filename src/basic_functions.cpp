
#include <map>
#include <vector>
#include <string>
#include <iostream>


std::string remove_whitespace(std::string text) {
    text.erase(0, text.find_first_not_of(" \t\r\n"));
    text.erase(text.find_last_not_of(" \t\r\n") + 1);
    return text;
}


std::vector<std::string> split_string(std::string text, char delimiter) {
    std::vector<std::string> the_split;

    int previous_index = 0;
    int index = text.find(delimiter);
    // std::cout << index << std::endl;
    while (index != std::string::npos) {
        std::string split_text = text.substr(previous_index, index);
        // std::cout << "added " << split_text << std::endl;
        the_split.push_back(split_text);
        text.erase(previous_index, index + 1);
        index = text.find(delimiter);
        // std::cout << text << " has " << delimiter << " at " << index << std::endl;
    }
    // std::cout << "added " << text << std::endl;
    the_split.push_back(text);

    return the_split;
}
