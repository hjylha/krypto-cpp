
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
    
}