
#include "basic_functions.h"
#include "codewordpuzzle.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

CodewordWordPair::CodewordWordPair(std::vector<int> codeword1, std::vector<int> codeword2, std::string word1, std::string word2) {
    codeword1 = codeword1;
    codeword2 = codeword2;
    word1 = word1;
    word2 = word2;
}


CodewordPuzzle::CodewordPuzzle(std::vector<std::vector<int>> codewords, std::vector<std::string> wordlist, std::string alphabet, std::vector<std::string> comments) {
    codewords = codewords;
    alphabet = alphabet;
    wordlist = wordlist;
    comments = comments;

    std::vector<int> nums = get_nums_in_codewords(codewords);
    for (int num : nums) {
        substitution_map[num] = not_found_symbol;
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

bool CodewordPuzzle::is_codeword_solved(std::vector<int> codeword) {
    for (int num : codeword) {
        if (substitution_map[num] == not_found_symbol) {
            return false;
        }
    }
    return true;
}