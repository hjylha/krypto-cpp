
#include "basic_functions.h"
#include "codewordpuzzle.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <string>
#include <utility>
#include <vector>

MatchingIndicesAndOthers::MatchingIndicesAndOthers(std::vector<std::pair<int, int>> matching_indices, std::vector<int> other_indices1, std::vector<int> other_indices2) {
    matching_indices = matching_indices;
    other_indices1 = other_indices1;
    other_indices2 = other_indices2;
}

MatchingIndicesAndOthers get_matching_indices(std::vector<int> codeword1, std::vector<int> codeword2) {
    std::vector<std::pair<int, int>> matching_indices;
    std::vector<int> other_indices1;
    std::vector<int> other_indices2;

    std::vector<int> nums_in_codeword1;

    int len1 = codeword1.size();
    int len2 = codeword2.size();

    for (int i1 = 0; i1 < len1; i1++) {
        if (std::find(nums_in_codeword1.begin(), nums_in_codeword1.end(), codeword1[i1]) == nums_in_codeword1.end()) {
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
    for (int i = 0; i < len2; i++) {
        if (std::find(nums_in_codeword1.begin(), nums_in_codeword1.end(), codeword2[i]) == nums_in_codeword1.end()) {
            other_indices2.push_back(i);
        }
    }

    return MatchingIndicesAndOthers(matching_indices, other_indices1, other_indices2);
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

bool do_words_match_to_matching_indices(std::string word1, std::string word2, MatchingIndicesAndOthers matching_indices_n_others) {
    std::vector<std::pair<int, int>> matching_indices = matching_indices_n_others.matching_indices;
    for (std::pair<int, int> index_pair : matching_indices) {
        if (word1[index_pair.first] != word2[index_pair.second]) {
            return false;
        }
    }
    for (int i1 : matching_indices_n_others.other_indices1) {
        if (word2.find(word1[i1]) != std::string::npos) {
            return false;
        }
    }
    for (int i2 : matching_indices_n_others.other_indices2) {
        if (word1.find(word2[i2]) != std::string::npos) {
            return false;
        }
    }
    return true;
}


CodewordWordPair::CodewordWordPair(std::vector<int> codeword1, std::vector<int> codeword2, std::string word1, std::string word2) {
    codeword1 = codeword1;
    codeword2 = codeword2;
    word1 = word1;
    word2 = word2;
}


CodewordPuzzle::CodewordPuzzle(std::vector<std::vector<int>> codewords, std::vector<std::string> wordlist, std::string alphabet, std::vector<std::string> comments) {
    codewords = codewords;
    alphabet = lowercase(alphabet);
    wordlist = wordlist;
    comments = comments;

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

    // what to do with problems?
    // if (max_num == 0 || min_num < 0) {}

    for (int i = 0; i <= max_num; i++) {
        substitution_vector.push_back(empty_symbol);
    }

    for (std::vector<int> codeword : codewords) {
        std::vector<std::string> words = get_matched_words(codeword, wordlist, -1);
        matched_words.push_back(words);
        matched_words_all.push_back(words);
    }

}

CodewordPuzzle::~CodewordPuzzle() {

}

std::vector<std::vector<int>> CodewordPuzzle::get_codewords() {
    return codewords;
}

std::vector<std::string> CodewordPuzzle::get_wordlist() {
    return wordlist;
}

std::vector<std::string> CodewordPuzzle::get_comments() {
    return comments;
}

std::vector<char> CodewordPuzzle::get_letters_in_substitution_vector() {
    std::vector<char> letters_in_substitution_vector;
    for (char letter : substitution_vector) {
        if (letter != empty_symbol) {
            letters_in_substitution_vector.push_back(letter);
        }
    }
    return letters_in_substitution_vector;
}

bool CodewordPuzzle::is_codeword_solved(std::vector<int> codeword) {
    for (int num : codeword) {
        if (substitution_vector[num] == empty_symbol) {
            return false;
        }
    }
    return true;
}

bool CodewordPuzzle::does_word_match_to_substitution_vector(std::string word, std::vector<int> codeword) {
    std::vector<char> letters_in_substitution_vector = get_letters_in_substitution_vector();
    for (int i = 0; i < word.length(); i++) {
        if (substitution_vector[codeword[i]] != empty_symbol && substitution_vector[codeword[i]] != word[i]) {
            return false;
        }
        bool condition = std::find(letters_in_substitution_vector.begin(), letters_in_substitution_vector.end(), word[i]) != letters_in_substitution_vector.end();
        if (substitution_vector[codeword[i]] == empty_symbol && condition) {
            return false;
        }
    }
return true;
}

void CodewordPuzzle::set_matched_words() {
    for (int i = 0; i < codewords.size(); i++) {
        std::vector<std::string> new_matched_words;
        for (std::string word : matched_words_all[i]) {
            if (does_word_match_to_substitution_vector(word, codewords[i])) {
                new_matched_words.push_back(word);
            }
        }
        matched_words[i] = new_matched_words;
    }
}

void CodewordPuzzle::clear_substitution_vector() {
    for (int i = 0; i < substitution_vector.size(); i++) {
        substitution_vector[i] = empty_symbol;
    }
}

int CodewordPuzzle::add_to_substitution_vector(int num, char letter, std::map<std::string, int> issues, bool override) {
    if (num < 0 || num >= substitution_vector.size()) {
        return issues["invalid number"];
    }
    if (letter == ' ') {
        substitution_vector[num] = empty_symbol;
        set_matched_words();
        return 0;
    }
    letter = std::tolower(letter);
    if (alphabet.find(letter) == std::string::npos) {
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
    set_matched_words();
    return 0;
}

int CodewordPuzzle::find_char_from_substitution_vector(char letter) {
    auto it = std::find(substitution_vector.begin(), substitution_vector.end(), letter);
    if (it == substitution_vector.end()) {
        return -1;
    }
    return it - substitution_vector.begin();
}

std::vector<int> CodewordPuzzle::find_codeword_with_least_matches() {
    std::vector<int> the_codeword;
    int least_matches = wordlist.size();
    for (int i = 0; i < codewords.size(); i++) {
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

std::vector<std::pair<std::string, std::string>> CodewordPuzzle::match_two_codewords(std::vector<int> codeword1, std::vector<int> codeword2, int maximum_matches) {
    std::vector<std::pair<std::string, std::string>> matching_pairs;

    MatchingIndicesAndOthers matching_indices_n_others = get_matching_indices(codeword1, codeword2);

    int index1 = std::find(codewords.begin(), codewords.end(), codeword1) - codewords.begin();
    int index2 = std::find(codewords.begin(), codewords.end(), codeword2) - codewords.begin();

    for (std::string word1 : matched_words[index1]) {
        for (std::string word2 : matched_words[index2]) {
            if (do_words_match_to_matching_indices(word1, word2, matching_indices_n_others)) {
                matching_pairs.push_back(std::pair<std::string, std::string>(word1, word2));
                if (matching_pairs.size() > maximum_matches) {
                    matching_pairs.clear();
                    return matching_pairs;
                }
            }
        }
    }


    return matching_pairs;
}

std::vector<CodewordWordPair> CodewordPuzzle::find_all_unique_pairs() {
    std::vector<CodewordWordPair> unique_pairs;
    

    return unique_pairs;
}
