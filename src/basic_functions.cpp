
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <cctype>


std::string remove_whitespace(std::string text) {
    text.erase(0, text.find_first_not_of(" \t\r\n"));
    text.erase(text.find_last_not_of(" \t\r\n") + 1);
    return text;
}

std::string add_whitespace(std::string text, int total_length) {
    text = text.substr(0, total_length);
    // std::string whitespace = " ";
    for (int i = 0; i < total_length - text.length(); i++) {
        text += " ";
    }
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

std::string lowercase(std::string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = std::tolower(text[i]);
    }
    return text;
}

std::string uppercase(std::string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = std::toupper(text[i]);
    }
    return text;
}


std::string codeword_as_str(std::vector<int> codeword) {
    std::string codeword_str = "";
    for (int num : codeword) {
        codeword_str += std::to_string(num);
        codeword_str += ",";
    }
    return codeword_str.substr(0, codeword_str.length() - 1);
}

std::string mass_replace(std::string text, std::vector<std::string> replacements) {
    // lots to do here
    int start_index;
    std::string text_to_find = "";
    for (int i = 0; i < replacements.size(); i++) {
        text_to_find = "%";
        text_to_find += std::to_string(i + 1);
        text_to_find += "%";
        start_index = text.find(text_to_find);
        text.replace(start_index, 3, replacements[i]);
    }
    return text;
}

std::vector<int> get_nums_in_codewords(std::vector<std::vector<int>> codewords) {
    std::vector<int> nums;
    for (std::vector<int> codeword : codewords) {
        for (int num : codeword) {
            if (std::find(nums.begin(), nums.end(), num) == nums.end()) {
                nums.push_back(num);
            }
        }
    }
    std::sort(nums.begin(), nums.end());
    return nums;
}


bool are_letters_in_alphabet(std::string word, std::string alphabet) {
    for (auto letter : word) {
        if (alphabet.find(std::tolower(letter)) == std::string::npos) {
            return false;
        }
    }
    return true;
}

bool does_word_match(std::string word, std::vector<int> codeword) {
    if (word.length() != codeword.size()) {
        return false;
    }
    std::map<int, char> substitution_map;
    char letter;
    // char letter_prev;
    int num;
    // int num_prev;
    for (int i = 0; i < word.length(); i++) {
        letter = word[i];
        num = codeword[i];
        auto it = substitution_map.find(num);
        if (it != substitution_map.end() && letter != substitution_map[num]) {
            return false;
        }
        if (it == substitution_map.end()) {
            substitution_map[num] = letter;
        }
        // for (int j = 0; j < i; j++) {
        //     letter_prev = word[j];
        //     num_prev = codeword[j];
        //     if (num == num_prev && letter != letter_prev) {
        //         return false;
        //     }
        //     if (num != num_prev && letter == letter_prev) {
        //         return false;
        //     }
        //     if (num == num_prev && letter == letter_prev) break;
        // }
    }
    return true;
}

std::vector<std::string> get_matched_words(std::vector<int> codeword, std::vector<std::string> wordlist, int maximum_matches) {
    std::vector<std::string> matched_words;
    int num_of_matches = 0;
    if (maximum_matches < 0) {
        maximum_matches = wordlist.size();
    }
    for (std::string word : wordlist) {
        if (does_word_match(word, codeword)) {
            matched_words.push_back(word);
            num_of_matches++;
            if (num_of_matches >= maximum_matches) {
                return matched_words;
            }
        }
    }
    return matched_words;
}
