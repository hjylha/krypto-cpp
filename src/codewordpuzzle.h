#ifndef CODEWORDPUZZLE_H_INCLUDED
#define CODEWORDPUZZLE_H_INCLUDED


#include <map>
#include <string>
#include <utility>
#include <vector>


struct MatchingIndicesAndOthers
{
private:

public:
    std::vector<std::pair<int, int>> matching_indices;
    std::vector<int> other_indices1;
    std::vector<int> other_indices2;
    MatchingIndicesAndOthers(std::vector<std::pair<int, int>> matching_indices, std::vector<int> other_indices1, std::vector<int> other_indices2);
    bool operator==(MatchingIndicesAndOthers other);
};

MatchingIndicesAndOthers get_matching_indices(std::vector<int> codeword1, std::vector<int> codeword2);
bool do_words_match_to_matching_indices(std::string word1, std::string word2, MatchingIndicesAndOthers matching_indices_n_others);

struct CodewordWordPair
{
private:

public:
    std::vector<int> codeword1;
    std::vector<int> codeword2;
    std::string word1;
    std::string word2;
    CodewordWordPair(std::vector<int> codeword1, std::vector<int> codeword2, std::string word1, std::string word2);
    bool empty();
};


class CodewordPuzzle
{
private:
    std::vector<std::vector<int>> codewords;
    std::string alphabet;
    std::vector<std::string> wordlist;
    std::vector<std::string> comments;
    std::vector<char> substitution_vector;
    std::vector<char> substitution_vector_saved;
    // std::map<int, std::vector<std::string>> wordlists;
    std::vector<std::vector<std::string>> matched_words_all;
    std::vector<std::vector<std::string>> matched_words;
public:
    char empty_symbol = '_';
    int num_of_codewords, num_of_words, num_of_letters, max_codeword_str_length, max_word_length, max_num_size;
    CodewordPuzzle();
    CodewordPuzzle(std::vector<std::vector<int>> the_codewords, std::vector<std::string> the_wordlist, std::string the_alphabet, std::vector<std::string> the_comments);
    ~CodewordPuzzle();
    std::string get_alphabet();
    std::vector<std::vector<int>> get_codewords();
    std::vector<std::string> get_wordlist();
    std::vector<std::string> get_comments();
    std::vector<char> get_letters_in_substitution_vector();
    std::vector<std::string> substitution_vector_in_two_lines();
    int count_solved_numbers();
    void save_substitution_vector();
    void load_substitution_vector();
    int get_codeword_index(std::vector<int> codeword);
    bool is_codeword_solved(std::vector<int> codeword);
    std::pair<int, int> count_solved_codewords();
    bool does_word_match_to_substitution_vector(std::string word, std::vector<int> codeword);
    void set_matched_words();
    std::vector<std::string> get_matched_words_for_codeword(int index_of_codeword);
    int get_num_of_matched_words(int index_of_codeword);
    std::vector<int> sort_codewords();
    void clear_substitution_vector();
    int add_to_substitution_vector(int num, char letter, std::map<std::string, int> issues, bool override);
    int find_char_from_substitution_vector(char letter);
    std::vector<int> find_codeword(std::string search_string);
    std::vector<int> find_codeword_with_least_matches();
    std::string get_decrypted_codeword(std::vector<int> codeword);
    std::vector<std::pair<std::string, std::string>> match_two_codewords(std::vector<int> codeword1, std::vector<int> codeword2, int maximum_matches);
    std::vector<CodewordWordPair> find_all_unique_pairs();
    std::pair<int, std::string> find_optimal_unique_pair();
};


#endif
