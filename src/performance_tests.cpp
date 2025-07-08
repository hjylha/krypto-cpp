
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
// #include <ctime>
#include <locale>
#include <clocale>
#include <chrono>
#include "basic_functions.h"
#include "file_operations.h"
#include "codewordpuzzle.h"
#include "codewordpuzzle_cli.h"

using std::cout, std::endl, std::vector, std::string, std::map, std::pair;


void show_elapsed_time(string description, std::chrono::time_point<std::chrono::high_resolution_clock> start_time, std::chrono::time_point<std::chrono::high_resolution_clock> end_time) {
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    cout << description << " " << duration.count() / 1000.0 << " milliseconds" << endl;
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "utf-8");
    // std::locale::global(std::locale("utf-8"));
    // std::cout.imbue(std::locale());

    auto start_time = std::chrono::high_resolution_clock::now();
    std::string lang = "";
    std::string cw_path = "";

    // std::cout << argc << " command line arguments detected:" << std::endl;
    // for (int i = 0; i < argc; i++) {
    //     std::cout << argv[i] << std::endl;
    // }

    auto end_time = std::chrono::high_resolution_clock::now();
    string description = "";

    cout << endl;

    string wordlist_fi_path = "wordlist_fi.txt";
    string wordlist_en_path = "wordlist_en.txt";

    start_time = std::chrono::high_resolution_clock::now();
    vector<string> wordlist_fi = get_wordlist(wordlist_fi_path);
    end_time = std::chrono::high_resolution_clock::now();
    description = "get_wordlist (fi)";
    show_elapsed_time(description, start_time, end_time);

    start_time = std::chrono::high_resolution_clock::now();
    vector<vector<string>> wordlist_vector_fi = get_wordlist_vector(wordlist_fi_path);
    end_time = std::chrono::high_resolution_clock::now();
    description = "get_wordlist_vector (fi)";
    show_elapsed_time(description, start_time, end_time);

    start_time = std::chrono::high_resolution_clock::now();
    vector<vector<int>> wordlist_int_fi = get_wordlist_as_int_vector(wordlist_fi_path);
    end_time = std::chrono::high_resolution_clock::now();
    description = "get_wordlist_as_int_vector (fi)";
    show_elapsed_time(description, start_time, end_time);

    start_time = std::chrono::high_resolution_clock::now();
    vector<vector<string>> wordlist_vector_fi2;
    for (string word : wordlist_fi) {
        wordlist_vector_fi2.push_back(utf8_split(word));
    }
    end_time = std::chrono::high_resolution_clock::now();
    description = "from string to vector (fi) (for-loop with strings)";
    show_elapsed_time(description, start_time, end_time);

    start_time = std::chrono::high_resolution_clock::now();
    vector<vector<string>> wordlist_vector_fi3;
    vector<int> word_lengths_fi;
    int len_fi = wordlist_fi.size();
    for (int i = 0; i < len_fi; i++) {
        wordlist_vector_fi3.push_back(utf8_split(wordlist_fi[i]));
        word_lengths_fi.push_back(wordlist_vector_fi3[i].size());
    }
    end_time = std::chrono::high_resolution_clock::now();
    description = "from string to vector (fi) (for-loop with indexes) +word lengths";
    show_elapsed_time(description, start_time, end_time);

    cout << endl;

    start_time = std::chrono::high_resolution_clock::now();
    vector<string> wordlist_en = get_wordlist(wordlist_en_path);
    end_time = std::chrono::high_resolution_clock::now();
    description = "get_wordlist (en)";
    show_elapsed_time(description, start_time, end_time);

    start_time = std::chrono::high_resolution_clock::now();
    vector<vector<string>> wordlist_vector_en = get_wordlist_vector(wordlist_en_path);
    end_time = std::chrono::high_resolution_clock::now();
    description = "get_wordlist_vector (en)";
    show_elapsed_time(description, start_time, end_time);

    start_time = std::chrono::high_resolution_clock::now();
    vector<vector<string>> wordlist_vector_en2;
    for (string word : wordlist_en) {
        wordlist_vector_en2.push_back(utf8_split(word));
    }
    end_time = std::chrono::high_resolution_clock::now();
    description = "from string to vector (en) (for-loop with strings)";
    show_elapsed_time(description, start_time, end_time);

    start_time = std::chrono::high_resolution_clock::now();
    vector<vector<string>> wordlist_vector_en3;
    int len_en = wordlist_en.size();
    for (int i = 0; i < len_en; i++) {
        wordlist_vector_en3.push_back(utf8_split(wordlist_en[i]));
    }
    end_time = std::chrono::high_resolution_clock::now();
    description = "from string to vector (fi) (for-loop with indexes)";
    show_elapsed_time(description, start_time, end_time);


    cout << endl;


    start_time = std::chrono::high_resolution_clock::now();
    string language_filepath = "language_file.csv";
    map<string, map<string, string>> language_map = get_language_map(language_filepath);
    end_time = std::chrono::high_resolution_clock::now();
    description = "get_language_map";
    show_elapsed_time(description, start_time, end_time);


    start_time = std::chrono::high_resolution_clock::now();
    string config_filepath = "krypto.cfg";
    map<string, map<string, string>> config = read_config(config_filepath);
    end_time = std::chrono::high_resolution_clock::now();
    description = "read_config";
    show_elapsed_time(description, start_time, end_time);


    start_time = std::chrono::high_resolution_clock::now();
    string codeword_filepath = "k24-51-52.csv";
    pair<vector<string>, vector<vector<int>>> comments_n_codewords = get_codewords(codeword_filepath);
    vector<vector<int>> codewords = comments_n_codewords.second;
    end_time = std::chrono::high_resolution_clock::now();
    description = "get_codewords (k24-51-52.csv)";
    show_elapsed_time(description, start_time, end_time);


    cout << endl;


    // start_time = std::chrono::high_resolution_clock::now();
    // vector<vector<vector<string>>> matched_words;
    // vector<vector<string>> word_vectors;
    // for (vector<int> codeword : codewords) {
    //     word_vectors = get_matched_words(codeword, wordlist_vector_fi, -1);
    //     matched_words.push_back(word_vectors);
    // }
    // end_time = std::chrono::high_resolution_clock::now();
    // description = "setting matched words (k24-51-52.csv)";
    // show_elapsed_time(description, start_time, end_time);

    // start_time = std::chrono::high_resolution_clock::now();
    // vector<vector<vector<string>>> matched_words2;
    // vector<vector<string>> word_vectors2;
    // for (vector<int> codeword : codewords) {
    //     word_vectors2 = get_matched_words2(codeword, wordlist_vector_fi, -1);
    //     matched_words2.push_back(word_vectors);
    // }
    // end_time = std::chrono::high_resolution_clock::now();
    // description = "setting matched words (try2) (k24-51-52.csv)";
    // show_elapsed_time(description, start_time, end_time);

    start_time = std::chrono::high_resolution_clock::now();
    vector<vector<vector<string>>> matched_words3;
    vector<vector<string>> word_vectors3;
    for (vector<int> codeword : codewords) {
        word_vectors3 = get_matched_words3(codeword, codeword.size(), wordlist_vector_fi, word_lengths_fi, -1);
        matched_words3.push_back(word_vectors3);
    }
    end_time = std::chrono::high_resolution_clock::now();
    description = "setting matched words (try3) (k24-51-52.csv)";
    show_elapsed_time(description, start_time, end_time);


    start_time = std::chrono::high_resolution_clock::now();
    vector<vector<vector<int>>> matched_words4;
    vector<vector<int>> word_vectors4;
    for (vector<int> codeword : codewords) {
        word_vectors4 = get_matched_words_int(codeword, wordlist_int_fi, -1);
        matched_words4.push_back(word_vectors4);
    }
    end_time = std::chrono::high_resolution_clock::now();
    description = "setting matched words (try3) (k24-51-52.csv)";
    show_elapsed_time(description, start_time, end_time);



    // PuzzleCLI puzzle_cli = PuzzleCLI();
    // std::vector<std::string> languages = puzzle_cli.get_languages();
    // for (int i = 1; i < argc; i++) {
    //     if (std::find(languages.begin(), languages.end(), argv[i]) != languages.end()) {
    //         lang = argv[i];
    //         continue;
    //     }
    //     if (does_path_exist(argv[i])) {
    //         cw_path = argv[i];
    //     }
    // }


    

    // auto end_time = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // std::cout << "Time elapsed to do things: " << duration.count() << " microseconds" << std::endl;

    return 0;
}