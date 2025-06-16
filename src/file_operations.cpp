#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


std::map<std::string, std::string> get_language_map(const std::string& filepath) {
    std::map<std::string, std::string> language_map;

    std::ifstream infile(filepath);
    std::string line, currentSection;

    if (!infile) {
        std::cerr << "Error: Cannot open file '" << filepath << "'\n";
        return config_map;
    }

    return language_map
}


std::map<std::string, std::map<std::string, std::string> read_config(const std::string& filepath) {
    std::ifstream infile(filepath);
    std::map<std::string, std::map<std::string, std::string>> config_map;
    std::string line, currentSection;

    if (!infile) {
        std::cerr << "Error: Cannot open file '" << filepath << "'\n";
        return config_map;
    }

    while (std::getline(infile, line)) {
        // Remove leading/trailing whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

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
                key.erase(0, key.find_first_not_of(" \t\r\n"));
                key.erase(key.find_last_not_of(" \t\r\n") + 1);
                value.erase(0, value.find_first_not_of(" \t\r\n"));
                value.erase(value.find_last_not_of(" \t\r\n") + 1);

                config_map[currentSection][key] = value;
            }
        }
    }
    return config_map;
}

std::vector<std::vector<int>> readCSVIntegers(const std::string& filepath) {
    std::vector<std::vector<int>> result;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filepath << std::endl;
        return result;
    }

    std::string line;
    while (std::getline(file, line)) {
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
            result.push_back(row);
        }
    }

    file.close();
    return result;
}
