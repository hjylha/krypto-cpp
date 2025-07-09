
#include "basic_functions.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cctype>


int get_minimum(int num1, int num2) {
    return (num1 < num2) ? num1 : num2;
}


std::string remove_whitespace(std::string text) {
    text.erase(0, text.find_first_not_of(" \t\r\n"));
    text.erase(text.find_last_not_of(" \t\r\n") + 1);
    return text;
}

std::string add_whitespace(std::string text, int total_length) {
    text = text.substr(0, total_length);
    // std::string whitespace = " ";
    int text_length = text.length();
    for (int i = 0; i < total_length - text_length; i++) {
        text += " ";
    }
    return text;
}

std::string add_whitespace(std::vector<std::string> text_vector, int total_length) {
    std::string text = "";
    int text_length = get_minimum(text_vector.size(), total_length);
    for (int i = 0; i < text_length; i++) {
        text += text_vector[i];
    }
    for (int i = 0; i < total_length - text_length; i++) {
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

std::vector<std::string> utf8_split(const std::string& text) {
    std::vector<std::string> result;
    size_t i = 0;
    const size_t len = text.length();

    while (i < len) {
        unsigned char c = static_cast<unsigned char>(text[i]);
        size_t char_len = 0;

        if ((c & 0x80) == 0) {
            // 1-byte character (ASCII)
            char_len = 1;
        } else if ((c & 0xE0) == 0xC0) {
            // 2-byte character
            char_len = 2;
        } else if ((c & 0xF0) == 0xE0) {
            // 3-byte character
            char_len = 3;
        } else if ((c & 0xF8) == 0xF0) {
            // 4-byte character
            char_len = 4;
        } else {
            // Invalid UTF-8, skip this byte
            char_len = 1;
        }

        if (i + char_len <= len) {
            result.push_back(text.substr(i, char_len));
        } else {
            // Malformed UTF-8 at the end of the string
            result.push_back(text.substr(i));
            break;
        }
        i += char_len;
    }
    return result;
}

std::string join_string(std::vector<std::string> text_vector, std::string delimiter) {
    std::string text = "";
    for (int i = 0; i < text_vector.size(); i++) {
        if (i != 0) {
            text += delimiter;
        }
        text += text_vector[i];
    }

    return text;
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

int find(std::vector<std::string> text_vector, std::string text) {
    int vector_length = text_vector.size();
    for (int i = 0; i < vector_length; i++) {
        if (text_vector[i] == text) {
            return i;
        }
    }
    return -1;
}

int find(std::vector<int> int_vector, int num) {
    int vector_length = int_vector.size();
    for (int i = 0; i < vector_length; i++) {
        if (int_vector[i] == num) {
            return i;
        }
    }
    return -1;
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
    std::string letter;
    for (int i = 0; i < word.length(); i++) {
        letter = word.substr(i, 1);
        if (alphabet.find(lowercase(letter)) == std::string::npos) {
            return false;
        }
    }
    return true;
}

bool are_letters_in_alphabet(std::vector<std::string> word_vector, std::vector<std::string> alphabet) {
    // std::string letter;
    for (std::string letter : word_vector) {
        // letter = word.substr(i, 1);
        if (std::find(alphabet.begin(), alphabet.end(), letter) == alphabet.end()) {
            return false;
        }
    }
    return true;
}

bool does_word_match(std::string word, std::vector<int> codeword) {
    // if (word == "öljytynnyri") {
    //     std::cout << word << " detected\n" << word[0] << " = " << word.substr(0, 1) << " != " << "ö" << std::endl;
    // }
    int word_length = word.length();
    if (word_length != codeword.size()) {
        return false;
    }
    std::map<int, std::string> substitution_map;
    std::vector<std::string> letters_found;
    std::string letter;
    int num;
    for (int i = 0; i < word_length; i++) {
        letter = word.substr(i, 1);
        // if (letter == "ö") {
        //     std::cout << letter << " discovered" << std::endl;
        // }
        // if (letter == "h") {
        //     std::cout << letter << " discovered" << std::endl;
        // }
        num = codeword[i];
        auto it = substitution_map.find(num);
        if (it != substitution_map.end() && letter != substitution_map[num]) {
            return false;
        }
        if (it == substitution_map.end()) {
            if (std::find(letters_found.begin(), letters_found.end(), letter) != letters_found.end()) {
                return false;
            }
            substitution_map[num] = letter;
            letters_found.push_back(letter);
        }
    }
    // another way to do this
    // char letter;
    // char letter_prev;
    // int num;
    // int num_prev;
    // for (int i = 0; i < word.length(); i++) {
    //     letter = word[i];
    //     num = codeword[i];
    //     for (int j = 0; j < i; j++) {
    //         letter_prev = word[j];
    //         num_prev = codeword[j];
    //         if (num == num_prev && letter != letter_prev) {
    //             return false;
    //         }
    //         if (num != num_prev && letter == letter_prev) {
    //             return false;
    //         }
    //         if (num == num_prev && letter == letter_prev) break;
    //     }
    // }
    return true;
}

bool does_word_match(std::vector<std::string> word_vector, std::vector<int> codeword) {
    int word_length = word_vector.size();
    if (word_length != codeword.size()) {
        return false;
    }
    std::map<int, std::string> substitution_map;
    std::vector<std::string> letters_found;
    std::string letter;
    int num;
    for (int i = 0; i < word_length; i++) {
        letter = word_vector[i];
        num = codeword[i];
        auto it = substitution_map.find(num);
        if (it != substitution_map.end() && letter != substitution_map[num]) {
            return false;
        }
        if (it == substitution_map.end()) {
            if (std::find(letters_found.begin(), letters_found.end(), letter) != letters_found.end()) {
                return false;
            }
            substitution_map[num] = letter;
            letters_found.push_back(letter);
        }
    }

    return true;
}

bool does_word_match(std::vector<std::string> word_vector, std::vector<int> codeword, int word_length, int codeword_length) {
    if (word_length != codeword_length) {
        return false;
    }
    std::map<int, std::string> substitution_map;
    std::vector<std::string> letters_found;
    std::string letter;
    int num;
    for (int i = 0; i < word_length; i++) {
        letter = word_vector[i];
        num = codeword[i];
        auto it = substitution_map.find(num);
        if (it != substitution_map.end() && letter != substitution_map[num]) {
            return false;
        }
        if (it == substitution_map.end()) {
            if (std::find(letters_found.begin(), letters_found.end(), letter) != letters_found.end()) {
                return false;
            }
            substitution_map[num] = letter;
            letters_found.push_back(letter);
        }
    }

    return true;
}

bool does_int_word_match(std::vector<int> int_vector, std::vector<int> codeword) {
    int word_length = int_vector.size();
    if (word_length != codeword.size()) {
        return false;
    }
    std::map<int, int> substitution_map;
    std::vector<int> letters_found;
    int letter;
    int num;
    for (int i = 0; i < word_length; i++) {
        letter = int_vector[i];
        num = codeword[i];
        auto it = substitution_map.find(num);
        if (it != substitution_map.end() && letter != substitution_map[num]) {
            return false;
        }
        if (it == substitution_map.end()) {
            if (std::find(letters_found.begin(), letters_found.end(), letter) != letters_found.end()) {
                return false;
            }
            substitution_map[num] = letter;
            letters_found.push_back(letter);
        }
    }

    return true;
}

bool does_int_word_match2(std::vector<int> int_vector, std::vector<int> codeword) {
    int word_length = int_vector.size();
    if (word_length != codeword.size()) {
        return false;
    }
    int letter;
    int letter_prev;
    int num;
    int num_prev;
    for (int i = 0; i < word_length; i++) {
        letter = int_vector[i];
        num = codeword[i];
        for (int j = 0; j < i; j++) {
            letter_prev = int_vector[j];
            num_prev = codeword[j];
            if (num == num_prev && letter != letter_prev) {
                return false;
            }
            if (num != num_prev && letter == letter_prev) {
                return false;
            }
            if (num == num_prev && letter == letter_prev) break;
        }
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

std::vector<std::vector<std::string>> get_matched_words(std::vector<int> codeword, std::vector<std::vector<std::string>> wordlist, int maximum_matches) {
    std::vector<std::vector<std::string>> matched_words;
    int num_of_matches = 0;
    if (maximum_matches < 0) {
        maximum_matches = wordlist.size();
    }
    for (std::vector<std::string> word_vector : wordlist) {
        if (does_word_match(word_vector, codeword)) {
            matched_words.push_back(word_vector);
            num_of_matches++;
            if (num_of_matches >= maximum_matches) {
                return matched_words;
            }
        }
    }
    return matched_words;
}

std::vector<std::vector<std::string>> get_matched_words2(std::vector<int> codeword, std::vector<std::vector<std::string>> wordlist, int maximum_matches) {
    std::vector<std::vector<std::string>> matched_words;
    int codeword_length = codeword.size();
    int num_of_matches = 0;
    if (maximum_matches < 0) {
        maximum_matches = wordlist.size();
    }
    int word_length;
    for (std::vector<std::string> word_vector : wordlist) {
        word_length = word_vector.size();
        if (does_word_match(word_vector, codeword, word_length, codeword_length)) {
            matched_words.push_back(word_vector);
            num_of_matches++;
            if (num_of_matches >= maximum_matches) {
                return matched_words;
            }
        }
    }
    return matched_words;
}

std::vector<std::vector<std::string>> get_matched_words3(std::vector<int> codeword, int codeword_length, std::vector<std::vector<std::string>> wordlist, std::vector<int> word_lengths) {
    std::vector<std::vector<std::string>> matched_words;
    int wordlist_length = wordlist.size();
    int word_length;
    std::vector<std::string> word_vector;
    for (int i = 0; i < wordlist_length; i++) {
        word_vector = wordlist[i];
        word_length = word_lengths[i];
        if (does_word_match(word_vector, codeword, word_length, codeword_length)) {
            matched_words.push_back(word_vector);
        }
    }
    return matched_words;
}

std::vector<std::vector<int>> get_matched_words_int(std::vector<int> codeword, std::vector<std::vector<int>> wordlist_int, int maximum_matches) {
    std::vector<std::vector<int>> matched_words;
    int wordlist_length = wordlist_int.size();
    int num_of_matches = 0;
    if (maximum_matches < 0) {
        maximum_matches = wordlist_length;
    }
    int word_length;
    std::vector<int> word_vector;
    for (int i = 0; i < wordlist_length; i++) {
        word_vector = wordlist_int[i];
        word_length = word_vector.size();
        if (does_int_word_match(word_vector, codeword)) {
            matched_words.push_back(word_vector);
            num_of_matches++;
            if (num_of_matches >= maximum_matches) {
                return matched_words;
            }
        }
    }
    return matched_words;
}

std::vector<std::vector<int>> get_matched_words_int2(std::vector<int> codeword, std::vector<std::vector<int>> wordlist_int) {
    std::vector<std::vector<int>> matched_words;
    int wordlist_length = wordlist_int.size();
    int word_length;
    std::vector<int> word_vector;
    for (int i = 0; i < wordlist_length; i++) {
        word_vector = wordlist_int[i];
        word_length = word_vector.size();
        if (does_int_word_match2(word_vector, codeword)) {
            matched_words.push_back(word_vector);
        }
    }
    return matched_words;
}
