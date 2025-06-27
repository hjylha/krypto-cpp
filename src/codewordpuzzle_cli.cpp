
#include "codewordpuzzle_cli.h"
#include <cctype>
#include <iterator>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "basic_functions.h"
#include "file_operations.h"
#include "codewordpuzzle.h"


bool yes_or_no_question(std::string question_text, std::pair<char, char> yes_no_pair, std::string help_text) {
    std::string y_dash_n = "";
    y_dash_n += std::toupper(yes_no_pair.first);
    y_dash_n += "/";
    y_dash_n += std::toupper(yes_no_pair.second);
    std::string answer;
    while (true) {
        std::cout << question_text << " " << y_dash_n << " ";
        std::getline(std::cin, answer);
        answer = lowercase(remove_whitespace(answer));
        if (!answer.empty() && answer[0] == yes_no_pair.first) {
            return true;
        }
        if (!answer.empty() && answer[0] == yes_no_pair.second) {
            return false;
        }
        std::cout << help_text << std::endl;
    }
}


PuzzleCLI::PuzzleCLI() {
    issues["invalid number"] = 1;
    issues["invalid letter"] = 2;
    issues["double letter"] = 3;

    language_map = get_language_map(DEFAULT_LANGUAGE_FILE_PATH);
    config = read_config(DEFAULT_CONFIG_PATH);

    for (auto p : language_map) {
        default_language = p.first;
        break;
    }
    language = default_language;

    current_language_map = language_map[language];

    wordlist_path = config[language][WORDLIST_PATH_KEY];
}

PuzzleCLI::~PuzzleCLI() {

}

std::pair<char, char> PuzzleCLI::get_yes_no_pair() {
    return std::pair<char, char>(current_language_map["yes"][0], current_language_map["no"][0]);
}

bool PuzzleCLI::yes_no_question(std::string question_text) {
    std::pair<char, char> yes_no_pair = get_yes_no_pair();
    std::string help_text = current_language_map["help_text"];
    return yes_or_no_question(question_text, yes_no_pair, help_text);
}

void PuzzleCLI::set_language(std::string new_language) {
    if (language_map.find(new_language) == language_map.end()) {
        language = default_language;
    }
    else {
        language = new_language;
    }
    current_language_map = language_map[language];
}

void PuzzleCLI::choose_language() {
    std::string languages = "";

    std::string choose_prompt = mass_replace(current_language_map["choose_language"], {languages});

    std::string language_answer;
    bool confirmed, try_again;
    while (true) {
        std::cout << choose_prompt << " ";
        std::getline(std::cin, language_answer);
        language_answer = lowercase(language_answer);
        if (config.find(language_answer) != config.end()) {
            set_language(language_answer);
            return;
        }
        if (language_answer == "" && language != "") {
            return;
        }
        confirmed = false;
        while (!confirmed) {
            std::string question_text = mass_replace(current_language_map["add_new_language_question"], {language_answer});
            bool add_new_language = yes_no_question(question_text);
            // TODO: maybe this should do something
            if (add_new_language) {
                set_language(language_answer);
                return;
            }
            else {
                try_again = yes_no_question(current_language_map["try_again_question"]);
                if (!try_again) {
                    return;
                }
            }
        }
    }
}

int PuzzleCLI::choose_codeword_path() {
    std::string found_csv_files_text = current_language_map["found_csv_files_text"];
    std::cout << found_csv_files_text << std::endl;
    std::vector<std::string> csv_files = get_csv_files_in_folder(config[language][CODEWORD_FOLDER_PATH_KEY]);
    for (std::string csv_file : csv_files) {
        std::cout << "/t" << csv_file << std::endl;
    }

    std::string path_answer, possible_codeword_path, question_text;
    bool try_again;
    while (true) {
        std::cout << current_language_map["codeword_path_prompt"];
        std::getline(std::cin, path_answer);
        possible_codeword_path = config[language][CODEWORD_FOLDER_PATH_KEY] + path_answer;
        if (does_path_exist(possible_codeword_path)) {
            codeword_path = possible_codeword_path;
            return 0;
        }
        question_text = mass_replace(current_language_map["file_not_found_try_again"], {path_answer});
        try_again = yes_no_question(question_text);
        if (!try_again) {
            return -1;
        }
    }
}

void PuzzleCLI::initialize_puzzle(std::string codeword_path, std::string wordlist_path) {
    codeword_path = codeword_path;
    std::pair<std::vector<std::string>, std::vector<std::vector<int>>> comments_n_codewords = get_codewords(codeword_path);
    std::vector<std::string> comments = comments_n_codewords.first;
    std::vector<std::vector<int>> codewords = comments_n_codewords.second;
    std::string alphabet = config[language][ALPHABET_KEY];
    if (wordlist_path == "") {
        wordlist_path = config[language][WORDLIST_PATH_KEY];
    }
    std::vector<std::string> full_wordlist = get_wordlist(wordlist_path);
    std::vector<std::string> wordlist;
    for (std::string word : full_wordlist) {
        if (are_letters_in_alphabet(word, alphabet)) {
            wordlist.push_back(word);
        }
    }

    puzzle = CodewordPuzzle(codewords, wordlist, alphabet, comments);

}
    
void PuzzleCLI::input_data_and_initialize_puzzle(std::string the_language, std::string the_codeword_path) {
    if (the_language == "") {
        choose_language();
    }
    if (the_codeword_path == "") {
        int exit_code = choose_codeword_path();
        if (exit_code == -1) {
            return;
        }
    }
    initialize_puzzle(the_codeword_path, "");
}

void PuzzleCLI::add_to_substitution_vector() {
    std::vector<int> numbers;
    std::vector<char> letters;

    std::cout << current_language_map["number_prompt"];
    std::string num_input_str;
    std::getline(std::cin, num_input_str);
    // int num_input = std::stoi(num_input_str);
    int num_input;
    std::vector<std::string> num_input_split = split_string(num_input_str, ',');
    for (std::string num_str : num_input_split) {
        num_str = remove_whitespace(num_str);
        try {
            num_input = std::stoi(num_str);
            numbers.push_back(num_input);
        } catch (const std::invalid_argument&) {
            // TODO: print something?
            return;
        }
    }

    std::cout << current_language_map["letter_prompt"];
    std::string letter_input;
    std::getline(std::cin, letter_input);
    std::vector<std::string> letter_input_split = split_string(letter_input, ',');
    for (std::string letter : letter_input_split) {
        letter = remove_whitespace(letter);
        // TODO: try-catch here?
        letters.push_back(tolower(letter[0]));
    }

    if (numbers.size() != letters.size()) {
        // TODO: message here?
        return;
    }

    int issue, num_already;
    std::string text_to_show;
    for (int i = 0; i < numbers.size(); i++) {
        issue = puzzle.add_to_substitution_vector(numbers[i], letters[i], issues, false);

        if (issue == 0) {
            continue;
        }

        if (issue == 1) {
            text_to_show = mass_replace(current_language_map["invalid_number_text"], {std::to_string(numbers[i])});
            std::cout << text_to_show << std::endl;
            continue;
        }

        if (issue == 2) {
            text_to_show = mass_replace(current_language_map["not_in_alphabet_text"], {std::to_string(letters[i]), puzzle.get_alphabet()});
            std::cout << text_to_show << std::endl;
            continue;
        }

        if (issue == 3) {
            num_already = puzzle.find_char_from_substitution_vector(letters[i]);
            text_to_show = mass_replace(current_language_map["already_in_table_text"], {std::to_string(letters[i]), std::to_string(num_already)});
            std::cout << text_to_show << std::endl;
        }
    }
}
    
void PuzzleCLI::set_codeword_as_word() {

    std::cout << current_language_map["codeword_prompt"] << std::endl;

    

}
    
void PuzzleCLI::print_pairs(CodewordWordPair) {

}
