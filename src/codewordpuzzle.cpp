
#include "basic_functions.h"
#include "codewordpuzzle.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

MatchingIndicesAndOthers::MatchingIndicesAndOthers(std::vector<std::pair<int, int>> the_matching_indices, std::vector<int> the_other_indices1, std::vector<int> the_other_indices2) {
    matching_indices = the_matching_indices;
    other_indices1 = the_other_indices1;
    other_indices2 = the_other_indices2;
}

bool MatchingIndicesAndOthers::operator==(MatchingIndicesAndOthers other) {
    int len_m1 = matching_indices.size();
    int len_m2 = other.matching_indices.size();
    if (len_m1 != len_m2) {
        return false;
    }
    int len11 = other_indices1.size();
    int len12 = other.other_indices1.size();
    if (len11 != len12) {
        return false;
    }
    int len21 = other_indices2.size();
    int len22 = other.other_indices2.size();
    if (len21 != len22) {
        return false;
    }
    for (int i = 0; i < len_m1; i++) {
        if (matching_indices[i].first != other.matching_indices[i].first || matching_indices[i].second != other.matching_indices[i].second) {
            return false;
        }
    }
    for (int i = 0; i < len11; i++) {
        if (other_indices1[i] != other.other_indices1[i]) {
            return false;
        }
    }
    for (int i = 0; i < len21; i++) {
        if (other_indices2[i] != other.other_indices2[i]) {
            return false;
        }
    }
    return true;
}

MatchingIndicesAndOthers get_matching_indices(std::vector<int> codeword1, std::vector<int> codeword2) {
    std::vector<std::pair<int, int>> matching_indices;
    std::vector<int> other_indices1;
    std::vector<int> other_indices2;

    std::vector<int> nums_in_codeword1;

    int len1 = codeword1.size();
    int len2 = codeword2.size();

    // auto end = nums_in_codeword1.end();

    for (int i1 = 0; i1 < len1; i1++) {
        if (std::find(nums_in_codeword1.begin(), nums_in_codeword1.end(), codeword1[i1]) == nums_in_codeword1.end()) {
        // if (std::find(nums_in_codeword1.begin(), end, codeword1[i1]) == end) {
        // if (find(nums_in_codeword1, codeword1[i1] == -1)) {
            nums_in_codeword1.push_back(codeword1[i1]);
        }
        else {
            continue;
        }
        bool found_match = false;
        for (int i2 = 0; i2 < len2; i2++) {
            if (codeword1[i1] == codeword2[i2]) {
                matching_indices.push_back(std::pair<int, int>(i1, i2));
                found_match = true;
                break;
            }
        }
        if (!found_match) {
            other_indices1.push_back(i1);
        }
    }
    bool found = false;
    for (int i = 0; i < len2; i++) {
        if (std::find(nums_in_codeword1.begin(), nums_in_codeword1.end(), codeword2[i]) == nums_in_codeword1.end()) {
        // if (std::find(nums_in_codeword1.begin(), end, codeword2[i]) == end) {
        // if (find(nums_in_codeword1, codeword2[i] == -1)) {
            for (int j = 0; j < other_indices2.size(); j++) {
                if (codeword2[other_indices2[j]] == codeword2[i]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                other_indices2.push_back(i);
            }
        }
    }

    return MatchingIndicesAndOthers(matching_indices, other_indices1, other_indices2);
}

// bool do_words_match_to_matching_indices(std::string word1, std::string word2, MatchingIndicesAndOthers matching_indices_n_others) {
bool do_words_match_to_matching_indices(std::vector<std::string> word_vector1, std::vector<std::string> word_vector2, MatchingIndicesAndOthers matching_indices_n_others) {
    std::vector<std::pair<int, int>> matching_indices = matching_indices_n_others.matching_indices;
    for (std::pair<int, int> index_pair : matching_indices) {
        if (word_vector1[index_pair.first] != word_vector2[index_pair.second]) {
            return false;
        }
    }
    auto end2 = word_vector2.end();
    for (int i1 : matching_indices_n_others.other_indices1) {
        // if (word_vector2.find(word_vector1[i1]) != std::string::npos) {
        // if (std::find(word_vector2.begin(), word_vector2.end(), word_vector1[i1]) != word_vector2.end()) {
        if (std::find(word_vector2.begin(), end2, word_vector1[i1]) != end2) {
        // if (find(word_vector2, word_vector1[i1]) > -1) {
            return false;
        }
    }
    auto end1 = word_vector1.end();
    for (int i2 : matching_indices_n_others.other_indices2) {
        // if (word_vector1.find(word_vector2[i2]) != std::string::npos) {
        // if (std::find(word_vector1.begin(), word_vector1.end(), word_vector2[i2]) != word_vector1.end()) {
        if (std::find(word_vector1.begin(), end1, word_vector2[i2]) != end1) {
        // if (find(word_vector1, word_vector2[i2]) > -1) {
            return false;
        }
    }
    return true;
}


// CodewordWordPair::CodewordWordPair(std::vector<int> the_codeword1, std::vector<int> the_codeword2, std::string the_word1, std::string the_word2) {
CodewordWordPair::CodewordWordPair(std::vector<int> the_codeword1, std::vector<int> the_codeword2, std::vector<std::string> the_word1, std::vector<std::string> the_word2) {
    codeword1 = the_codeword1;
    codeword2 = the_codeword2;
    word1 = the_word1;
    word2 = the_word2;
}

bool CodewordWordPair::empty() {
    if (codeword1.empty()) {
        return true;
    }
    if (codeword2.empty()) {
        return true;
    }
    // if (word1 == "") {
    if (word1.empty()) {
        return true;
    }
    // if (word2 == "") {
    if (word2.empty()) {
        return true;
    }
    return false;
}


CodewordPuzzle::CodewordPuzzle() {

}

// CodewordPuzzle::CodewordPuzzle(std::vector<std::vector<int>> the_codewords, std::vector<std::string> the_wordlist, std::string the_alphabet, std::vector<std::string> the_comments) {
CodewordPuzzle::CodewordPuzzle(std::vector<std::vector<int>> the_codewords, std::vector<std::vector<std::string>> the_wordlist, std::vector<std::string> the_alphabet, std::vector<std::string> the_comments) {
    codewords = the_codewords;
    // alphabet = lowercase(the_alphabet);
    alphabet.clear();
    for (std::string letter : the_alphabet) {
        alphabet.push_back(lowercase(letter));
    }
    wordlist = the_wordlist;
    comments = the_comments;

    // std::cout << alphabet << std::endl;

    num_of_codewords = codewords.size();
    num_of_words = wordlist.size();

    std::vector<int> nums = get_nums_in_codewords(codewords);
    int max_num = 0;
    int min_num = nums.size();
    for (int num : nums) {
        if (num > max_num) {
            max_num = num;
            continue;
        }
        if (num < min_num) {
            min_num = num;
        }
    }
    num_of_letters = max_num;

    // what to do with problems?
    // if (max_num == 0 || min_num < 0) {}

    for (int i = 0; i <= num_of_letters; i++) {
        substitution_vector.push_back(empty_symbol);
        substitution_vector_saved.push_back(empty_symbol);
    }

    std::vector<std::vector<std::string>> word_vectors;
    for (std::vector<int> codeword : codewords) {
        // std::vector<std::string> words = get_matched_words(codeword, wordlist, -1);
        word_vectors = get_matched_words(codeword, wordlist, num_of_words);
        matched_words.push_back(word_vectors);
        matched_words_all.push_back(word_vectors);
    }

    max_num_size = std::to_string(num_of_codewords).length();
    max_codeword_str_length = 0;
    max_word_length = 0;
    std::string codeword_str;
    for (std::vector<int> codeword : codewords) {
        codeword_str = codeword_as_str(codeword);
        if (codeword_str.length() > max_codeword_str_length) {
            max_codeword_str_length = codeword_str.length();
        }
        if (codeword.size() > max_word_length) {
            max_word_length = codeword.size();
        }
    }
}

CodewordPuzzle::~CodewordPuzzle() {

}

std::vector<std::string> CodewordPuzzle::get_alphabet() {
    return alphabet;
}

std::vector<std::vector<int>> CodewordPuzzle::get_codewords() {
    return codewords;
}

std::vector<std::vector<std::string>> CodewordPuzzle::get_wordlist() {
    return wordlist;
}

std::vector<std::string> CodewordPuzzle::get_comments() {
    return comments;
}

std::vector<std::string> CodewordPuzzle::get_letters_in_substitution_vector() {
    std::vector<std::string> letters_in_substitution_vector;
    for (std::string letter : substitution_vector) {
        if (letter != empty_symbol) {
            letters_in_substitution_vector.push_back(letter);
        }
    }
    return letters_in_substitution_vector;
}

std::vector<std::string> CodewordPuzzle::substitution_vector_in_two_lines() {
    std::vector<std::string> lines;
    std::string line1 = "";
    std::string line2 = "";
    std::string delimiter = " | ";
    std::string letter;
    for (int i = 1; i <= num_of_letters; i++) {
        if (i > 1) {
            line1 += delimiter;
            line2 += delimiter;
        }
        line1 += std::to_string(i);
        letter = "";
        if (substitution_vector[i] == empty_symbol) {
            letter += ' ';
        }
        else {
            letter += substitution_vector[i];
        }
        line2 += add_whitespace(utf8_split(letter), std::to_string(i).length());
    }
    lines.push_back(line1);
    lines.push_back(line2);

    return lines;
}

int CodewordPuzzle::count_solved_numbers() {
    int num_of_solved_nums = 0;
    for (int i = 1; i <= num_of_letters; i++) {
        if (substitution_vector[i] != empty_symbol) {
            num_of_solved_nums++;
        }
    }
    return num_of_solved_nums;
}

void CodewordPuzzle::save_substitution_vector() {
    for (int i = 0; i < num_of_codewords; i++) {
        substitution_vector_saved[i] = substitution_vector[i];
    }
}

void CodewordPuzzle::load_substitution_vector() {
    for (int i = 0; i < num_of_codewords; i++) {
        substitution_vector[i] = substitution_vector_saved[i];
    }
    set_matched_words_from_start();
}

int CodewordPuzzle::get_codeword_index(std::vector<int> codeword) {
    auto it = std::find(codewords.begin(), codewords.end(), codeword);
    if (it == codewords.end()) {
        return -1;
    }
    return it - codewords.begin();
}

bool CodewordPuzzle::is_codeword_solved(std::vector<int> codeword) {
    for (int num : codeword) {
        if (substitution_vector[num] == empty_symbol) {
            return false;
        }
    }
    return true;
}

std::pair<int, int> CodewordPuzzle::count_solved_codewords() {
    int num_of_solved_codewords = 0;
    int num_of_words_in_wordlist = 0;
    std::string word;
    std::vector<std::string> word_vector;
    for (int i = 0; i < num_of_codewords; i++) {
        if (is_codeword_solved(codewords[i])) {
            num_of_solved_codewords++;
            word = get_decrypted_codeword(codewords[i]);
            word_vector = utf8_split(word);
            if (std::find(matched_words_all[i].begin(), matched_words_all[i].end(), word_vector) != matched_words_all[i].end()) {
                num_of_words_in_wordlist++;
            }
        }
    }
    return std::pair<int, int>(num_of_solved_codewords, num_of_words_in_wordlist);
}

// bool CodewordPuzzle::does_word_match_to_substitution_vector(std::string word, std::vector<int> codeword) {
bool CodewordPuzzle::does_word_match_to_substitution_vector(std::vector<std::string> word_vector, std::vector<int> codeword) {
    std::vector<std::string> letters_in_substitution_vector = get_letters_in_substitution_vector();
    for (int i = 0; i < word_vector.size(); i++) {
        // if (substitution_vector[codeword[i]] != empty_symbol && substitution_vector[codeword[i]] != word[i]) {
        if (substitution_vector[codeword[i]] != empty_symbol && substitution_vector[codeword[i]] != word_vector[i]) {
            return false;
        }
        // bool condition = std::find(letters_in_substitution_vector.begin(), letters_in_substitution_vector.end(), word[i]) != letters_in_substitution_vector.end();
        bool condition = std::find(letters_in_substitution_vector.begin(), letters_in_substitution_vector.end(), word_vector[i]) != letters_in_substitution_vector.end();
        if (substitution_vector[codeword[i]] == empty_symbol && condition) {
            return false;
        }
    }
return true;
}

void CodewordPuzzle::set_matched_words() {
    for (int i = 0; i < num_of_codewords; i++) {
        std::vector<std::vector<std::string>> new_matched_words;
        for (std::vector<std::string> word_vector : matched_words[i]) {
            if (does_word_match_to_substitution_vector(word_vector, codewords[i])) {
                new_matched_words.push_back(word_vector);
            }
        }
        matched_words[i] = new_matched_words;
    }
}

void CodewordPuzzle::set_matched_words_from_start() {
    for (int i = 0; i < num_of_codewords; i++) {
        std::vector<std::vector<std::string>> new_matched_words;
        for (std::vector<std::string> word_vector : matched_words_all[i]) {
            if (does_word_match_to_substitution_vector(word_vector, codewords[i])) {
                new_matched_words.push_back(word_vector);
            }
        }
        matched_words[i] = new_matched_words;
    }
}

// std::vector<std::string> CodewordPuzzle::get_matched_words_for_codeword(int index_of_codeword) {
std::vector<std::vector<std::string>> CodewordPuzzle::get_matched_words_for_codeword(int index_of_codeword) {
    return matched_words[index_of_codeword];
}

int CodewordPuzzle::get_num_of_matched_words(int index_of_codeword) {
    return matched_words[index_of_codeword].size();
}

std::vector<int> CodewordPuzzle::sort_codewords() {
    std::vector<int> sorted_indices;
    std::vector<int> comparison;
    // int comparison_num;
    for (int i = 0; i < num_of_codewords; i++) {
        sorted_indices.push_back(i);
        // comparison_num = matched_words[i].size();
        comparison.push_back(matched_words[i].size());
    }
    std::sort(sorted_indices.begin(), sorted_indices.end(), [&comparison](int i1, int i2) {return comparison[i1] < comparison[i2];});
    std::vector<int> final_sorted_indices;
    int starting_index = 0;
    for (int i = 0; i < num_of_codewords; i++) {
        if (comparison[sorted_indices[i]] > 0) {
            final_sorted_indices.push_back(sorted_indices[i]);
        }
    }
    return final_sorted_indices;
}

void CodewordPuzzle::clear_substitution_vector() {
    for (int i = 0; i < substitution_vector.size(); i++) {
        substitution_vector[i] = empty_symbol;
    }
    set_matched_words_from_start();
}

int CodewordPuzzle::add_to_substitution_vector(int num, std::string letter, std::map<std::string, int> issues, bool override) {
    if (num < 0 || num >= substitution_vector.size()) {
        return issues["invalid number"];
    }
    if (letter == " " || letter == "" || letter == empty_symbol) {
        substitution_vector[num] = empty_symbol;
        // std::cout << "Added in CodewordPuzzle " << num << " = " << empty_symbol << std::endl;
        set_matched_words_from_start();
        return 0;
    }
    // letter = std::tolower(letter);
    letter = lowercase(letter);
    // if (alphabet.find(letter) == std::string::npos) {
    if (std::find(alphabet.begin(), alphabet.end(), letter) == alphabet.end()) {
        return issues["invalid letter"];
    }
    int previous_num = find_char_from_substitution_vector(letter);
    if (previous_num != -1 && !override) {
        return issues["double letter"];
    }
    if (previous_num != -1 && override) {
        substitution_vector[previous_num] = empty_symbol;
    }
    substitution_vector[num] = letter;
    // std::cout << "Added in CodewordPuzzle " << num << " = " << letter << std::endl;
    // std::cout << "Confirmation: " << num << " = " << substitution_vector[num] << std::endl;
    // std::cout << "Confirmation2: " << find_char_from_substitution_vector(letter) << " = " << letter << std::endl;
    set_matched_words();
    return 0;
}

// void CodewordPuzzle::set_codeword_to_word(int codeword_index, std::string word) {
//     // TODO: REWORK NEEDED
//     for (int i = 0; i < word.length(); i++) {
//         // add_to_substitution_vector(codewords[codeword_index][i], word[i], std::map<std::string, int>(), true);
//         add_to_substitution_vector(codewords[codeword_index][i], word.substr(i, 1), std::map<std::string, int>(), true);
//     }
// }

void CodewordPuzzle::set_codeword_to_word(int codeword_index, std::vector<std::string> word_vector) {
    // TODO: REWORK NEEDED
    for (int i = 0; i < word_vector.size(); i++) {
        // add_to_substitution_vector(codewords[codeword_index][i], word[i], std::map<std::string, int>(), true);
        add_to_substitution_vector(codewords[codeword_index][i], word_vector[i], std::map<std::string, int>(), true);
    }
}

int CodewordPuzzle::find_char_from_substitution_vector(std::string letter) {
    auto it = std::find(substitution_vector.begin(), substitution_vector.end(), letter);
    if (it == substitution_vector.end()) {
        return -1;
    }
    return it - substitution_vector.begin();
}

std::vector<int> CodewordPuzzle::find_codeword(std::string search_string) {
    std::vector<int> search_result;

    search_string = remove_whitespace(search_string);
    int codeword_index;
    try {
        codeword_index = std::stoi(search_string) - 1;
        return codewords[codeword_index];
    } catch (const std::invalid_argument&) {

    }

    std::vector<int> the_codeword;
    std::vector<std::string> nums_as_str = split_string(search_string, ',');
    for (std::string num_as_str : nums_as_str) {
        num_as_str = remove_whitespace(num_as_str);
        try {
            the_codeword.push_back(std::stoi(num_as_str));
        } catch (const std::invalid_argument&) {
            return search_result;
        }
    }

    for (std::vector<int> codeword : codewords) {
        if (codeword == the_codeword) {
            return the_codeword;
        }
    }

    return search_result;
}

std::vector<int> CodewordPuzzle::find_codeword_with_least_matches() {
    std::vector<int> the_codeword;
    int least_matches = wordlist.size();
    for (int i = 0; i < num_of_codewords; i++) {
        if (is_codeword_solved(codewords[i])) continue;

        int num_of_matches = matched_words[i].size();
        if (num_of_matches > 0 && num_of_matches < least_matches) {
            least_matches = num_of_matches;
            the_codeword = codewords[i];
        }
    }
    return the_codeword;
}

std::string CodewordPuzzle::get_decrypted_codeword(std::vector<int> codeword) {
    std::string decrypted_codeword = "";
    for (int i = 0; i < codeword.size(); i++) {
        decrypted_codeword += substitution_vector[codeword[i]];
    }
    return decrypted_codeword;
}

// std::vector<std::pair<std::string, std::string>> CodewordPuzzle::match_two_codewords(std::vector<int> codeword1, std::vector<int> codeword2, int maximum_matches) {
//     std::vector<std::pair<std::string, std::string>> matching_pairs;

//     MatchingIndicesAndOthers matching_indices_n_others = get_matching_indices(codeword1, codeword2);

//     // std::vector<std::pair<int, int>> m_indices = matching_indices_n_others.matching_indices;
//     // std::vector<int> o_i1 = matching_indices_n_others.other_indices1;
//     // std::vector<int> o_i2 = matching_indices_n_others.other_indices2;
//     // std::cout << "size of matching_indices: " << m_indices.size() << std::endl;
//     // for (auto p : m_indices) {
//     //     std::cout << p.first << ", " << p.second << std::endl;
//     // }
//     // for (int i : o_i1) {
//     //     std::cout << i << ", ";
//     // }
//     // std::cout << std::endl;
//     // for (int i : o_i2) {
//     //     std::cout << i << ", ";
//     // }
//     // std::cout << std::endl;

//     int index1 = std::find(codewords.begin(), codewords.end(), codeword1) - codewords.begin();
//     int index2 = std::find(codewords.begin(), codewords.end(), codeword2) - codewords.begin();

//     // std::cout << "index1=" << index1 << "   index2=" << index2 << std::endl;

//     for (std::string word1 : matched_words[index1]) {
//         for (std::string word2 : matched_words[index2]) {
//             if (do_words_match_to_matching_indices(word1, word2, matching_indices_n_others)) {
//                 matching_pairs.push_back(std::pair<std::string, std::string>(word1, word2));
//                 if (matching_pairs.size() > maximum_matches) {
//                     matching_pairs.clear();
//                     return matching_pairs;
//                 }
//             }
//         }
//     }


//     return matching_pairs;
// }
// std::vector<std::string>

// std::vector<std::pair<std::string, std::string>> CodewordPuzzle::match_two_codewords(int codeword_index1, int codeword_index2, int maximum_matches) {
std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>> CodewordPuzzle::match_two_codewords(int codeword_index1, int codeword_index2, int maximum_matches) {
    std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>> matching_pairs;
    int num_of_matched_pairs = 0;

    MatchingIndicesAndOthers matching_indices_n_others = get_matching_indices(codewords[codeword_index1], codewords[codeword_index2]);

    for (std::vector<std::string> word_vector1 : matched_words[codeword_index1]) {
        for (std::vector<std::string> word_vector2 : matched_words[codeword_index2]) {
            if (do_words_match_to_matching_indices(word_vector1, word_vector2, matching_indices_n_others)) {
                matching_pairs.push_back(std::pair<std::vector<std::string>, std::vector<std::string>>(word_vector1, word_vector2));
                num_of_matched_pairs++;
                // if (matching_pairs.size() > maximum_matches) {
                if (num_of_matched_pairs > maximum_matches) {
                    matching_pairs.clear();
                    return matching_pairs;
                }
            }
        }
    }


    return matching_pairs;
}

std::vector<CodewordWordPair> CodewordPuzzle::find_all_unique_pairs() {

    // std::cout << "starting search" << std::endl;

    std::vector<CodewordWordPair> unique_pairs;
    std::vector<int> sorted_indices = sort_codewords();
    // std::vector<int> sorted_indices;
    // for (int i = 0; i < num_of_codewords; i++) {
    //     if (!matched_words[i].empty()) {
    //         sorted_indices.push_back(i);
    //     }
    // }

    // std::cout << "indices sorted" << std::endl;
    // std::cout << sorted_indices.size() << " good indices" << std::endl;

    // int checked_things = 0;
    // int good_things = 0;

    int index1, index2;
    std::vector<int> codeword1, codeword2;

    int num_of_good_codewords = sorted_indices.size();
    bool is_codeword1_solved, is_codeword2_solved;
    for (int i1 = 0; i1 < num_of_good_codewords; i1++) {
        index1 = sorted_indices[i1];
        codeword1 = codewords[index1];
        // is_codeword1_solved = is_codeword_solved(codewords[sorted_indices[i1]]);
        is_codeword1_solved = is_codeword_solved(codeword1);
        for (int i2 = i1 + 1; i2 < num_of_good_codewords; i2++) {
            index2 = sorted_indices[i2];
            codeword2 = codewords[index2];
            // checked_things++;
            // is_codeword2_solved = is_codeword_solved(codewords[sorted_indices[i2]]);
            is_codeword2_solved = is_codeword_solved(codeword2);
            if (is_codeword1_solved && is_codeword2_solved) {
                continue;
            }
            // std::vector<std::pair<std::string, std::string>> matched_pairs = match_two_codewords(sorted_indices[i1], sorted_indices[i2], 1);
            // std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>> matched_pairs = match_two_codewords(sorted_indices[i1], sorted_indices[i2], 1);
            std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>> matched_pairs = match_two_codewords(index1, index2, 1);
            if (!matched_pairs.empty()) {
                // good_things++;
                // std::cout << checked_things << " pair is good number " << good_things << std::endl;
                // unique_pairs.push_back(CodewordWordPair(codewords[sorted_indices[i1]], codewords[sorted_indices[i2]], matched_pairs[0].first, matched_pairs[0].second));
                unique_pairs.push_back(CodewordWordPair(codeword1, codeword2, matched_pairs[0].first, matched_pairs[0].second));
            }
        }
    }
    // std::cout << checked_things << " things checked, " << good_things << " good things found" << std::endl;

    return unique_pairs;
}

std::pair<int, std::string> CodewordPuzzle::find_optimal_unique_pair() {
    std::vector<CodewordWordPair> unique_pairs = find_all_unique_pairs();
    if (unique_pairs.empty()) {
        return std::pair<int, std::string>(-1, "");
    }
    std::map<std::pair<int, std::string>, int> num_of_appearances;
    std::vector<int> codeword1, codeword2;
    std::string word1, word2;
    // std::vector<std::string> word1, word2;
    int index1, index2;
    for (CodewordWordPair cw_w_pair : unique_pairs) {
        codeword1 = cw_w_pair.codeword1;
        index1 = std::find(codewords.begin(), codewords.end(), codeword1) - codewords.begin();
        // word1 = cw_w_pair.word1;
        word1 = join_string(cw_w_pair.word1, "");
        if (!is_codeword_solved(codeword1)) {
            if (num_of_appearances.count(std::pair<int, std::string>(index1, word1)) == 0) {
                num_of_appearances[std::pair<int, std::string>(index1, word1)] = 1;
            }
            else {
                num_of_appearances[std::pair<int, std::string>(index1, word1)] += 1;
            }
        }
        codeword2 = cw_w_pair.codeword2;
        // word2 = cw_w_pair.word2;
        word2 = join_string(cw_w_pair.word2, "");
        index2 = std::find(codewords.begin(), codewords.end(), codeword2) - codewords.begin();
        if (!is_codeword_solved(codeword2)) {
            if (num_of_appearances.count(std::pair<int, std::string>(index2, word2)) == 0) {
                num_of_appearances[std::pair<int, std::string>(index2, word2)] = 1;
            }
            else {
                num_of_appearances[std::pair<int, std::string>(index2, word2)] += 1;
            }
        }
    }
    std::pair<int, std::string> optimal_pair;
    std::pair<int, std::string> match;
    int max_num_of_appearances = 0;
    for (auto match_n_num : num_of_appearances) {
        match = match_n_num.first;
        if (match_n_num.second > max_num_of_appearances) {
            optimal_pair = match;
            max_num_of_appearances = match_n_num.second;
        }
    }
    return optimal_pair;
}
