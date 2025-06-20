#ifndef CODEWORDPUZZLE_H_INCLUDED
#define CODEWORDPUZZLE_H_INCLUDED


#include <map>
#include <string>
#include <utility>
#include <vector>


struct CodewordWordPair
{
private:

public:
    std::vector<int> codeword1;
    std::vector<int> codeword2;
    std::string word1;
    std::string word2;
    CodewordWordPair(std::vector<int> codeword1, std::vector<int> codeword2, std::string word1, std::string word2);
};


class CodewordPuzzle
{
private:
    char empty_symbol = '_';
    std::vector<std::vector<int>> codewords;
    std::string alphabet;
    std::vector<std::string> wordlist;
    std::vector<std::string> comments;
    std::vector<char> substitution_vector;
    // std::map<int, std::vector<std::string>> wordlists;
    std::vector<std::vector<std::string>> matched_words_all;
    std::vector<std::vector<std::string>> matched_words;
public:
    CodewordPuzzle(std::vector<std::vector<int>> codewords, std::vector<std::string> wordlist, std::string alphabet, std::vector<std::string> comments);
    ~CodewordPuzzle();
    std::vector<std::vector<int>> get_codewords();
    std::vector<std::string> get_wordlist();
    std::vector<std::string> get_comments();
    std::vector<char> get_letters_in_substitution_vector();
    bool is_codeword_solved(std::vector<int> codeword);
    bool does_word_match_to_substitution_vector(std::string word, std::vector<int> codeword);
    void set_matched_words();
    void clear_substitution_vector();
    int add_to_substitution_vector(int num, char letter, std::map<std::string, int> issues, bool override);
    int find_char_from_substitution_vector(char letter);
    std::vector<int> find_codeword_with_least_matches();
    std::string get_decrypted_codeword(std::vector<int> codeword);
    std::vector<std::pair<std::string, std::string>> match_two_codewords(std::vector<int> codeword1, std::vector<int> codeword2, int maximum_matches);  
    std::vector<CodewordWordPair> find_all_unique_pairs();
    CodewordWordPair find_optimal_unique_pair();
};


#endif
