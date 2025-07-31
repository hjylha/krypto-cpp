
#include <algorithm>
#include <string>
#include <utility>
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

using std::cout, std::endl, std::vector, std::string, std::map, std::pair, std::chrono::time_point, std::chrono::high_resolution_clock;


double show_elapsed_time(string description, time_point<high_resolution_clock> start_time, time_point<high_resolution_clock> end_time, string unit) {
    double elapsed_time;
    if (unit == "micro") {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        elapsed_time = duration.count();
        cout << description << " " << elapsed_time << " microseconds" << endl;
        return elapsed_time;
    }
    if (unit == "milli") {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        elapsed_time = duration.count();
        cout << description << " " << elapsed_time / 1000.0 << " milliseconds" << endl;
        return elapsed_time;
    }
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    elapsed_time = duration.count();
    cout << description << " " << elapsed_time / 1000000.0 << " seconds" << endl;
    return elapsed_time;
}


class PerformanceTest
{
private:
    string DEFAULT_LANGUAGE_FILE_PATH = "language_file.csv";
    string DEFAULT_CONFIG_PATH = "krypto.cfg";
    string NAME_KEY = "name";
    string ALPHABET_KEY = "alphabet";
    string ALPHABET_UPPER_KEY = "alphabet_upper";
    string WORDLIST_PATH_KEY = "wordlist_path";
    string CODEWORD_FOLDER_PATH_KEY = "codeword_folder_path";

    string language_tag = "";
    string codeword_path = "";

    string wordlist_path = "";

    map<string, map<string, string>> language_map;
    map<string, map<string, string>> config;

    std::vector<std::string> alphabet;
    std::vector<std::string> alphabet_upper;
    std::map<std::string, int> alphabet_map;

    vector<string> wordlist;


    vector<vector<int>> wordlist_int;
    vector<int> word_lengths;
    vector<vector<int>> codewords;
    vector<int> codeword_lengths;
    vector<string> comments;
public:
    PerformanceTest(string language, string codewords_filepath)
    {
        language_tag = language;
        codeword_path = codewords_filepath;
    }

    ~PerformanceTest() {

    }

    void read_config_and_set_values() {
        config = read_config(DEFAULT_CONFIG_PATH);

        alphabet = utf8_split(config[language_tag][ALPHABET_KEY]);
        alphabet_upper = utf8_split(config[language_tag][ALPHABET_UPPER_KEY]);
        alphabet_map = get_alphabet_map(config[language_tag][ALPHABET_KEY]);

        wordlist_path = config[language_tag][WORDLIST_PATH_KEY];
    }

    double get_language_map_duration() {
        auto start_time = std::chrono::high_resolution_clock::now();
        language_map = get_language_map(DEFAULT_LANGUAGE_FILE_PATH);
        auto end_time = std::chrono::high_resolution_clock::now();
        string description = "get_language_map";
        return show_elapsed_time(description, start_time, end_time, "micro");
    }

    double read_config_duration() {
        auto start_time = std::chrono::high_resolution_clock::now();
        read_config_and_set_values();
        auto end_time = std::chrono::high_resolution_clock::now();

        string description = "read_config";
        return show_elapsed_time(description, start_time, end_time, "micro");
    }

    double get_wordlist_duration() {
        
        if (wordlist_path == "") {
            read_config_and_set_values();
        }

        auto start_time = std::chrono::high_resolution_clock::now();
        wordlist = get_wordlist(wordlist_path);
        auto end_time = std::chrono::high_resolution_clock::now();
        string description = "get_wordlist (";
        description += wordlist_path;
        description += ")";
        return show_elapsed_time(description, start_time, end_time, "milli");
    }

    // std::pair<std::vector<int>, std::vector<std::vector<int>>> wordlist_stuff = get_wordlist_as_int_vector_plus(wordlist_path, alphabet_map);
    double get_wordlist_as_int_vector_plus_duration() {
        if (wordlist_path == "") {
            read_config_and_set_values();
        }

        auto start_time = std::chrono::high_resolution_clock::now();
        pair<vector<int>, vector<vector<int>>> wordlist_plus = get_wordlist_as_int_vector_plus(wordlist_path, alphabet_map);
        auto end_time = std::chrono::high_resolution_clock::now();

        wordlist_int = wordlist_plus.second;
        word_lengths = wordlist_plus.first;

        string description = "get_wordlist_as_int_vector_plus (";
        description += wordlist_path;
        description += ")";
        return show_elapsed_time(description, start_time, end_time, "milli");
    }

    double get_codewords_duration() {
        auto start_time = std::chrono::high_resolution_clock::now();
        // string codeword_filepath = "k24-51-52.csv";
        pair<vector<string>, vector<vector<int>>> comments_n_codewords = get_codewords(codeword_path);
        vector<vector<int>> codewords = comments_n_codewords.second;
        auto end_time = std::chrono::high_resolution_clock::now();
        string description = "get_codewords (";
        description += codeword_path;
        description += ")";
        return show_elapsed_time(description, start_time, end_time, "micro");
    }

    double get_codewords_and_comments_duration() {
        auto start_time = std::chrono::high_resolution_clock::now();
        // string codeword_filepath = "k24-51-52.csv";
        CodewordsAndComments codewords_n_comments = get_codewords_and_comments(codeword_path);
        // vector<vector<int>> codewords = comments_n_codewords.second;
        auto end_time = std::chrono::high_resolution_clock::now();

        codewords = codewords_n_comments.codewords;
        codeword_lengths = codewords_n_comments.codeword_lengths;
        comments = codewords_n_comments.comments;

        string description = "get_codewords (";
        description += codeword_path;
        description += ")";
        return show_elapsed_time(description, start_time, end_time, "micro");
    }


    double get_matched_words_duration() {
        auto start_time = std::chrono::high_resolution_clock::now();
        vector<vector<vector<int>>> matched_words5;
        vector<vector<int>> word_vectors5;
        for (vector<int> codeword : codewords) {
            word_vectors5 = get_matched_words_int2(codeword, wordlist_int);
            matched_words5.push_back(word_vectors5);
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        string description = "setting matched words (int2) (";
        description += codeword_path;
        description += ")";
        return show_elapsed_time(description, start_time, end_time, "");
    }

    double run_performance_tests() {
        vector<double> durations;
        // language_map & config???
        
        durations.push_back(get_wordlist_as_int_vector_plus_duration());

        durations.push_back((get_codewords_and_comments_duration()));

        durations.push_back(get_matched_words_duration());

        double total_duration = sum_vector(durations);

        cout << "Total duration: " << total_duration / 1000000.0 << " seconds" << endl;

        return total_duration;
    }
};




int main(int argc, char* argv[])
{
    setlocale(LC_ALL, ".UTF-8");
    // std::locale::global(std::locale("utf-8"));
    // std::cout.imbue(std::locale());

    auto start_time = std::chrono::high_resolution_clock::now();
    string lang = "";
    string cw_path = "";

    std::cout << argc << " command line arguments detected:" << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    bool run_fi = false;
    bool run_en = false;
    string lang_fi = "fi";
    string lang_en = "en";

    if (argc == 1) {
        run_fi = true;
        run_en = true;
    }
    else {
        for (int i = 1; i < argc; i++) {
            if (argv[i] == lang_fi) {
                run_fi = true;
                continue;
            }
            if (argv[i] == lang_en) {
                run_en = true;
            }
        }
    }


    auto end_time = std::chrono::high_resolution_clock::now();
    string description = "";

    cout << endl;


    start_time = std::chrono::high_resolution_clock::now();
    string language_filepath = "language_file.csv";
    map<string, map<string, string>> language_map = get_language_map(language_filepath);
    end_time = std::chrono::high_resolution_clock::now();
    description = "get_language_map";
    show_elapsed_time(description, start_time, end_time, "micro");


    start_time = std::chrono::high_resolution_clock::now();
    string config_filepath = "krypto.cfg";
    map<string, map<string, string>> config = read_config(config_filepath);
    end_time = std::chrono::high_resolution_clock::now();
    description = "read_config";
    show_elapsed_time(description, start_time, end_time, "micro");

    cout << endl;

    
    

    if (run_fi) {
        string wordlist_fi_path = "wordlist_fi.txt";

        start_time = std::chrono::high_resolution_clock::now();
        vector<string> wordlist_fi = get_wordlist(wordlist_fi_path);
        end_time = std::chrono::high_resolution_clock::now();
        description = "get_wordlist (fi)";
        show_elapsed_time(description, start_time, end_time, "milli");

        start_time = std::chrono::high_resolution_clock::now();
        vector<vector<string>> wordlist_vector_fi = get_wordlist_vector(wordlist_fi_path);
        end_time = std::chrono::high_resolution_clock::now();
        description = "get_wordlist_vector (fi)";
        show_elapsed_time(description, start_time, end_time, "milli");

        start_time = std::chrono::high_resolution_clock::now();
        vector<vector<int>> wordlist_int_fi = get_wordlist_as_int_vector(wordlist_fi_path);
        end_time = std::chrono::high_resolution_clock::now();
        description = "get_wordlist_as_int_vector (fi)";
        show_elapsed_time(description, start_time, end_time, "milli");

        start_time = std::chrono::high_resolution_clock::now();
        vector<vector<int>> wordlist_int_fi2 = get_wordlist_int(wordlist_fi_path);
        end_time = std::chrono::high_resolution_clock::now();
        description = "get_wordlist_int (fi)";
        show_elapsed_time(description, start_time, end_time, "milli");


        start_time = std::chrono::high_resolution_clock::now();
        vector<vector<string>> wordlist_vector_fi2;
        for (string word : wordlist_fi) {
            wordlist_vector_fi2.push_back(utf8_split(word));
        }
        end_time = std::chrono::high_resolution_clock::now();
        description = "from string to vector (fi) (for-loop with strings)";
        show_elapsed_time(description, start_time, end_time, "milli");

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
        show_elapsed_time(description, start_time, end_time, "milli");

        cout << endl;

        start_time = std::chrono::high_resolution_clock::now();
        string codeword_filepath = "k24-51-52.csv";
        pair<vector<string>, vector<vector<int>>> comments_n_codewords = get_codewords(codeword_filepath);
        vector<vector<int>> codewords = comments_n_codewords.second;
        end_time = std::chrono::high_resolution_clock::now();
        description = "get_codewords (k24-51-52.csv)";
        show_elapsed_time(description, start_time, end_time, "micro");

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
        // show_elapsed_time(description, start_time, end_time, "");

        // start_time = std::chrono::high_resolution_clock::now();
        // vector<vector<vector<string>>> matched_words2;
        // vector<vector<string>> word_vectors2;
        // for (vector<int> codeword : codewords) {
        //     word_vectors2 = get_matched_words2(codeword, wordlist_vector_fi, -1);
        //     matched_words2.push_back(word_vectors);
        // }
        // end_time = std::chrono::high_resolution_clock::now();
        // description = "setting matched words (try2) (k24-51-52.csv)";
        // show_elapsed_time(description, start_time, end_time, "");

        start_time = std::chrono::high_resolution_clock::now();
        vector<vector<vector<string>>> matched_words3;
        vector<vector<string>> word_vectors3;
        for (vector<int> codeword : codewords) {
            word_vectors3 = get_matched_words3(codeword, codeword.size(), wordlist_vector_fi, word_lengths_fi);
            matched_words3.push_back(word_vectors3);
        }
        end_time = std::chrono::high_resolution_clock::now();
        description = "setting matched words (try3) (k24-51-52.csv)";
        show_elapsed_time(description, start_time, end_time, "");


        start_time = std::chrono::high_resolution_clock::now();
        vector<vector<vector<int>>> matched_words4;
        vector<vector<int>> word_vectors4;
        for (vector<int> codeword : codewords) {
            word_vectors4 = get_matched_words_int(codeword, wordlist_int_fi, -1);
            matched_words4.push_back(word_vectors4);
        }
        end_time = std::chrono::high_resolution_clock::now();
        description = "setting matched words (int) (k24-51-52.csv)";
        show_elapsed_time(description, start_time, end_time, "");


        start_time = std::chrono::high_resolution_clock::now();
        vector<vector<vector<int>>> matched_words5;
        vector<vector<int>> word_vectors5;
        for (vector<int> codeword : codewords) {
            word_vectors5 = get_matched_words_int2(codeword, wordlist_int_fi);
            matched_words5.push_back(word_vectors4);
        }
        end_time = std::chrono::high_resolution_clock::now();
        description = "setting matched words (int2) (k24-51-52.csv)";
        show_elapsed_time(description, start_time, end_time, "");

        cout << "\n" << endl;

        PerformanceTest pt = PerformanceTest(lang_fi, codeword_filepath);

        pt.run_performance_tests();

        cout << "\n" << endl;


    }


    if (run_en) {
        string wordlist_en_path = "wordlist_en.txt";

        start_time = std::chrono::high_resolution_clock::now();
        vector<string> wordlist_en = get_wordlist(wordlist_en_path);
        end_time = std::chrono::high_resolution_clock::now();
        description = "get_wordlist (en)";
        show_elapsed_time(description, start_time, end_time, "milli");

        start_time = std::chrono::high_resolution_clock::now();
        vector<vector<string>> wordlist_vector_en = get_wordlist_vector(wordlist_en_path);
        end_time = std::chrono::high_resolution_clock::now();
        description = "get_wordlist_vector (en)";
        show_elapsed_time(description, start_time, end_time, "milli");

        start_time = std::chrono::high_resolution_clock::now();
        vector<vector<string>> wordlist_vector_en2;
        for (string word : wordlist_en) {
            wordlist_vector_en2.push_back(utf8_split(word));
        }
        end_time = std::chrono::high_resolution_clock::now();
        description = "from string to vector (en) (for-loop with strings)";
        show_elapsed_time(description, start_time, end_time, "milli");

        start_time = std::chrono::high_resolution_clock::now();
        vector<vector<string>> wordlist_vector_en3;
        int len_en = wordlist_en.size();
        for (int i = 0; i < len_en; i++) {
            wordlist_vector_en3.push_back(utf8_split(wordlist_en[i]));
        }
        end_time = std::chrono::high_resolution_clock::now();
        description = "from string to vector (en) (for-loop with indexes)";
        show_elapsed_time(description, start_time, end_time, "milli");

        cout << endl;

        string codeword_filepath = "cw25-05-12.csv";

        PerformanceTest pt = PerformanceTest(lang_en, codeword_filepath);

        pt.run_performance_tests();

        cout << "\n" << endl;
    }


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