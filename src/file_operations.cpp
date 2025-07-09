
#include <cstddef>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "basic_functions.h"


bool does_path_exist(std::string path) {
    std::ifstream infile(path);
    return infile.good();
}

std::map<std::string, std::map<std::string, std::string>> get_language_map(const std::string& filepath) {
    std::map<std::string, std::map<std::string, std::string>> language_map;

    std::ifstream file(filepath);
    std::string line, currentSection;

    if (!file) {
        std::cerr << "Error: Cannot open file '" << filepath << "'\n";
        return language_map;
    }
    std::vector<std::string> first_line;
    std::vector<std::string> split_line;

    while (std::getline(file, line)) {
        
        line = remove_whitespace(line);
        if (line.empty() || line[0] == '#') continue;

        split_line = split_string(line, ';');
        if (first_line.empty()) {
            first_line = split_line;
            for (int i = 1; i < first_line.size(); i++) {
                if (first_line[i] == "") break;

                language_map[first_line[i]] = std::map<std::string, std::string>();
            }
            continue;
        }

        for (int i = 1; i < first_line.size(); i++) {
            if (first_line[i] == "") break;
            
            language_map[first_line[i]][split_line[0]] = split_line[i];
        }
    }
    file.close();
    return language_map;
}


std::map<std::string, std::map<std::string, std::string>> read_config(const std::string& filepath) {
    std::ifstream file(filepath);
    std::map<std::string, std::map<std::string, std::string>> config_map;
    std::string line, currentSection;

    if (!file) {
        std::cerr << "Error: Cannot open file '" << filepath << "'\n";
        return config_map;
    }

    while (std::getline(file, line)) {
        
        line = remove_whitespace(line);
        if (line.empty() || line[0] == '#') continue;

        if (line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
            config_map[currentSection] = std::map<std::string, std::string>();
        } else {
            auto eqPos = line.find('=');
            if (eqPos != std::string::npos && !currentSection.empty()) {
                std::string key = line.substr(0, eqPos);
                std::string value = line.substr(eqPos + 1);

                // Trim whitespace
                key = remove_whitespace(key);
                value = remove_whitespace(value);

                config_map[currentSection][key] = value;
            }
        }
    }
    file.close();
    return config_map;
}

std::vector<std::string> get_wordlist(const std::string& filepath) {
    std::vector<std::string> wordlist;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filepath << std::endl;
        return wordlist;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = remove_whitespace(line);
        // lowercase?
        wordlist.push_back(lowercase(line));
    }
    file.close();

    return wordlist;
}

std::vector<std::vector<std::string>> get_wordlist_vector(const std::string& filepath) {
    std::vector<std::vector<std::string>> wordlist;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filepath << std::endl;
        return wordlist;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = lowercase(remove_whitespace(line));
        // lowercase?
        wordlist.push_back(utf8_split(line));
    }
    file.close();

    return wordlist;
}

std::vector<std::vector<int>> get_wordlist_as_int_vector(const std::string& filepath) {
    std::vector<std::vector<int>> wordlist;
    std::map<std::string, int> letter_to_int_map;
    int num_of_letters = 0;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filepath << std::endl;
        return wordlist;
    }

    std::string line;
    std::vector<std::string> line_vector;
    std::vector<int> num_vector;
    int num;

    while (std::getline(file, line)) {
        num_vector.clear();
        line = lowercase(remove_whitespace(line));
        if (line == "") {
            continue;
        }
        // lowercase?
        line_vector = utf8_split(line);
        for (std::string letter : line_vector) {
            num = letter_to_int_map[letter];
            if (num == 0) {
                num_of_letters++;
                letter_to_int_map[letter] = num_of_letters;
                num_vector.push_back(num_of_letters);
                continue;
            }
            num_vector.push_back(num);
        }
        wordlist.push_back(num_vector);
    }
    file.close();

    return wordlist;
}

std::vector<std::vector<int>> get_wordlist_int(const std::string& filepath){
    std::vector<std::vector<int>> wordlist;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filepath << std::endl;
        return wordlist;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = remove_whitespace(line);

        std::vector<int> row;
        std::stringstream ss(line);
        std::string value;

        while (std::getline(ss, value, ',')) {
            try {
                row.push_back(std::stoi(value));
            } catch (const std::invalid_argument&) {
                // Handle parse error (skip non-integer values)
                continue;
            }
        }

        if (!row.empty()) {
            wordlist.push_back(row);
        }
    }
    file.close();

    return wordlist;
}

std::pair<std::vector<std::string>, std::vector<std::vector<int>>> get_codewords(const std::string& filepath) {
    std::vector<std::string> comments;
    std::vector<std::vector<int>> codewords;
    std::fstream file(filepath);

    // char buffer[65536];
    // file.rdbuf()->pubsetbuf(buffer, sizeof(buffer));

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filepath << std::endl;
        return std::pair(comments, codewords);
    }

    std::string line;
    std::vector<std::string> str_vector;
    std::vector<int> num_vector;
    while (std::getline(file, line)) {
        size_t pos = 0;
        if ((pos = line.find('#')) != std::string::npos) {
            line.erase(0, pos + 1);
            comments.push_back(remove_whitespace(line));
            continue;
        }
        str_vector.clear();
        num_vector.clear();
        size_t last = 0;
        
        while ((pos = line.find(',', last)) != std::string::npos) {
            str_vector.emplace_back(line, last, pos - last);
            last = pos + 1;
        }
        if (last) {
            str_vector.emplace_back(line, last);
        }
        for (std::string num_str : str_vector) {
            if (num_str != "") {
                num_vector.push_back(std::stoi(num_str));
            }
            
        }
        if (!num_vector.empty()) {
            codewords.push_back(num_vector);
        }
        
    }


    // another way
    // while (std::getline(file, line)) {
    //     line = remove_whitespace(line);

    //     if (line.front() == '#') {
    //         line.erase(0, 1);
    //         line = remove_whitespace(line);
    //         comments.push_back(line);
    //         continue;
    //     }

    //     std::vector<int> row;
    //     std::stringstream ss(line);
    //     std::string value;

    //     while (std::getline(ss, value, ',')) {
    //         try {
    //             row.push_back(std::stoi(value));
    //         } catch (const std::invalid_argument&) {
    //             // Handle parse error (skip non-integer values)
    //             continue;
    //         }
    //     }

    //     if (!row.empty()) {
    //         codewords.push_back(row);
    //     }
    // }
    file.close();

    return std::pair(comments, codewords);
}

// std::vector<std::vector<int>> readCSVIntegers(const std::string& filepath) {
//     std::vector<std::vector<int>> result;
//     std::ifstream file(filepath);

//     if (!file.is_open()) {
//         std::cerr << "Could not open file: " << filepath << std::endl;
//         return result;
//     }

//     std::string line;
//     while (std::getline(file, line)) {
//         std::vector<int> row;
//         std::stringstream ss(line);
//         std::string value;

//         while (std::getline(ss, value, ',')) {
//             try {
//                 row.push_back(std::stoi(value));
//             } catch (const std::invalid_argument&) {
//                 // Handle parse error (skip non-integer values)
//                 continue;
//             }
//         }

//         if (!row.empty()) {
//             result.push_back(row);
//         }
//     }

//     file.close();
//     return result;
// }

std::vector<std::string> get_csv_files_in_folder(std::string folder_path) {
    std::vector<std::string> csv_files;
    if (folder_path == "") {
        folder_path = std::filesystem::current_path().string();
    }

    try {
        for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
            if (entry.is_regular_file() && entry.path().extension() == ".csv") {
                // csv_files.push_back(entry.path().filename().string());
                csv_files.push_back(entry.path().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        // std::string complete_folder_path = std::filesystem::current_path().string() + folder_path;
        // try {
        //     for (const auto& entry : std::filesystem::directory_iterator(complete_folder_path)) {
        //         if (entry.is_regular_file() && entry.path().extension() == ".csv") {
        //             csv_files.push_back(entry.path().filename().string());
        //     }
        //     }
        // } catch (const std::filesystem::filesystem_error& e) {
        //     std::cerr << "Filesystem error: " << e.what() << std::endl;
        // }
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    return csv_files;
}
