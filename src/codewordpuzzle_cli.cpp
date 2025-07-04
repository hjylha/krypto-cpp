
#include <cctype>
#include <iterator>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <iostream>
#include <chrono>
#include "basic_functions.h"
#include "file_operations.h"
#include "codewordpuzzle.h"
#include "codewordpuzzle_cli.h"


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

    for (auto p : config) {
        default_language = p.first;
        // std::cout << "Default language is " << default_language << std::endl;
        // break;
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

std::vector<std::string> PuzzleCLI::get_languages() {
    std::vector<std::string> languages;
    for (auto item : config) {
        languages.push_back(item.first);
    }
    return languages;
}

void PuzzleCLI::choose_language() {
    std::vector<std::string> languages = get_languages();
    std::string languages_str = languages[0];
    if (languages.size() > 1) {
        for (int i = 1; i < languages.size(); i++) {
            languages_str += ", ";
            languages_str += languages[i];
        }
    }

    std::string choose_prompt = mass_replace(current_language_map["choose_language"], {languages_str});

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
        std::cout << "    " << csv_file << std::endl;
    }

    std::string path_answer, possible_codeword_path, question_text;
    bool try_again;
    while (true) {
        std::cout << current_language_map["codeword_path_prompt"];
        std::getline(std::cin, path_answer);
        possible_codeword_path = config[language][CODEWORD_FOLDER_PATH_KEY] + path_answer;
        if (does_path_exist(possible_codeword_path)) {
            codeword_path = possible_codeword_path;
            // std::cout << "Chosen codeword path: " << codeword_path << std::endl;
            return 0;
        }
        question_text = mass_replace(current_language_map["file_not_found_try_again"], {path_answer});
        try_again = yes_no_question(question_text);
        if (!try_again) {
            return -1;
        }
    }
}

void PuzzleCLI::initialize_puzzle(std::string the_codeword_path, std::string the_wordlist_path) {
    codeword_path = the_codeword_path;
    std::pair<std::vector<std::string>, std::vector<std::vector<int>>> comments_n_codewords = get_codewords(codeword_path);
    std::vector<std::string> comments = comments_n_codewords.first;
    std::vector<std::vector<int>> codewords = comments_n_codewords.second;
    std::string alphabet = config[language][ALPHABET_KEY];
    if (the_wordlist_path == "") {
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
    else {
        set_language(the_language);
    }
    if (the_codeword_path == "") {
        int exit_code = choose_codeword_path();
        if (exit_code == -1) {
            return;
        }
    }
    else if (does_path_exist(the_codeword_path)) {
        codeword_path = the_codeword_path;
    }
    initialize_puzzle(codeword_path, "");
}

void PuzzleCLI::restart() {
    puzzle.clear_substitution_vector();
}

void PuzzleCLI::exit_program() {
    running = false;
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
            std::cout << "problems with numbers" << std::endl;
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
            // std::cout << "Added " << numbers[i] << " = " << letters[i] << std::endl;
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
    // print_substitution_vector();
}
    
void PuzzleCLI::set_codeword_as_word() {

    std::cout << current_language_map["codeword_prompt"];
    std::string codeword_input;
    std::getline(std::cin, codeword_input);

    std::vector<int> the_codeword = puzzle.find_codeword(codeword_input);

    if (the_codeword.empty()) {
        std::string invalid_codeword_text = mass_replace(current_language_map["invalid_codeword_text"], {codeword_input});
        std::cout << invalid_codeword_text << std::endl;
        return;
    }

    std::cout << current_language_map["word_prompt"];
    std::string word_input;
    std::getline(std::cin, word_input);
    word_input = lowercase(word_input);

    if (!does_word_match(word_input, the_codeword)) {
        std::string no_match_text = mass_replace(current_language_map["no_match_text"], {word_input, codeword_as_str(the_codeword)});
        std::cout << no_match_text << std::endl;
        return;
    }

    // TODO: is word in wordlist

    for (int i = 0; i < word_input.length(); i++) {
        puzzle.add_to_substitution_vector(the_codeword[i], word_input[i], issues, true);
    }
    // puzzle.set_matched_words();
}
    
void PuzzleCLI::print_pairs(CodewordWordPair codeword_word_pair) {
    std::vector<int> codeword1 = codeword_word_pair.codeword1;
    std::vector<int> codeword2 = codeword_word_pair.codeword2;
    std::string word1 = codeword_word_pair.word1;
    std::string word2 = codeword_word_pair.word2;

    if (puzzle.is_codeword_solved(codeword1)) {
        word1 += solved_char;
    }
    if (puzzle.is_codeword_solved(codeword2)) {
        word2 += solved_char;
    }

    int codeword_index1 = puzzle.get_codeword_index(codeword1) + 1;
    int codeword_index2 = puzzle.get_codeword_index(codeword2) + 1;

    std::string codeword1_str = codeword_as_str(codeword1);
    std::string codeword2_str = codeword_as_str(codeword2);

    std::string part1 = add_whitespace(std::to_string(codeword_index1), puzzle.max_num_size);
    part1 += " ";
    part1 += add_whitespace(codeword1_str, puzzle.max_codeword_str_length);

    std::string part2 = add_whitespace(std::to_string(codeword_index2), puzzle.max_num_size);
    part1 += " ";
    part1 += add_whitespace(codeword2_str, puzzle.max_codeword_str_length);

    std::string part3 = add_whitespace(uppercase(word1), puzzle.max_word_length);
    std::string part4 = add_whitespace(uppercase(word2), puzzle.max_word_length);

    std::cout << part1 << "   " << part2 << "   " << part3 << "  " << part4 << std::endl; 
}

std::vector<CodewordWordPair> PuzzleCLI::find_unique_pairs() {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<CodewordWordPair> unique_pairs = puzzle.find_all_unique_pairs();
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    double time_taken = duration.count() / 1000.0;
    std::string unique_pairs_found_text = mass_replace(current_language_map["unique_pairs_found_text"], {std::to_string(unique_pairs.size()), std::to_string(time_taken)});
    std::cout << unique_pairs_found_text << std::endl;

    std::string solved_marker = "";
    solved_marker += solved_char;
    std::cout << mass_replace(current_language_map["solved_words_note"], {solved_marker}) << std::endl;

    for (CodewordWordPair codeword_word_pair : unique_pairs) {
        print_pairs(codeword_word_pair);
    }
    // is return necessary?
    return unique_pairs;
}

void PuzzleCLI::print_solving_stats(double elapsed_time) {
    std::cout << "\n" << mass_replace(current_language_map["solving_time_with_steps_text"], {std::to_string(elapsed_time)}) << std::endl;

    std::pair<int, int> word_counts = puzzle.count_solved_codewords();
    int num_of_solved_codewords = word_counts.first;
    int num_of_found_words = word_counts.second;
    std::cout << mass_replace(current_language_map["found_codewords_text"], {std::to_string(num_of_solved_codewords), std::to_string(puzzle.num_of_codewords)}) << std::endl;
    std::cout << mass_replace(current_language_map["found_codewords_in_wordlist_text"], {std::to_string(num_of_found_words)}) << std::endl;

    int num_of_solved_numbers = puzzle.count_solved_numbers();
    std::cout << mass_replace(current_language_map["substitution_table_decipher_text"], {std::to_string(num_of_solved_numbers), std::to_string(puzzle.num_of_letters)});
}

void PuzzleCLI::try_to_solve_puzzle_fully_methodically() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
    try_to_solve_puzzle_methodically(start_time);
}

void PuzzleCLI::try_to_solve_puzzle_methodically(std::chrono::time_point<std::chrono::high_resolution_clock> start_time) {
    int found_words = 0;

    std::pair<int, std::string> optimal_pair = puzzle.find_optimal_unique_pair();
    while (optimal_pair.first > -1) {
        found_words++;

        std::string codeword_str = codeword_as_str(puzzle.get_codewords()[optimal_pair.first]);
        std::string part1 = add_whitespace(std::to_string(found_words), puzzle.max_num_size);
        std::string part2 = current_language_map["best_match_text"];
        std::string part3 = add_whitespace(std::to_string(optimal_pair.first + 1), puzzle.max_num_size);
        std::string part4 = add_whitespace(codeword_str, puzzle.max_codeword_str_length);
        std::string part5 = add_whitespace(uppercase(optimal_pair.second), puzzle.max_word_length);
        std::cout << part1 << " " << part2 << part3 << "  " << part4 << "  " << part5 << std::endl;
        
        puzzle.set_codeword_to_word(optimal_pair.first, optimal_pair.second);
        // puzzle.set_matched_words();

        optimal_pair = puzzle.find_optimal_unique_pair();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1000.0;
    print_solving_stats(elapsed_time);
}

void PuzzleCLI::try_to_solve_puzzle_with_steps() {

}

void PuzzleCLI::print_substitution_vector() {
    std::vector<std::string> lines = puzzle.substitution_vector_in_two_lines();
    for (std::string line : lines) {
        std::cout << uppercase(line) << std::endl;
    }
}

void PuzzleCLI::print_initial_info() {
    std::cout << mass_replace(current_language_map["language"], {config[language]["name"]}) << std::endl;
    std::cout << mass_replace(current_language_map["codewords_in_file"], {std::to_string(puzzle.num_of_codewords), codeword_path}) << std::endl;
    std::cout << mass_replace(current_language_map["words_in_file"], {std::to_string(puzzle.num_of_words), wordlist_path}) << std::endl;
    if (!puzzle.get_comments().empty()) {
        std::cout << current_language_map["comments"] << std::endl;
        for (std::string comment_line : puzzle.get_comments()) {
            std::cout << comment_line << std::endl;
        }
    }

}

void PuzzleCLI::print_missing_chars() {
    std::cout << current_language_map["missing_letters_text"] << std::endl;
    std::string letter_str = "";
    for (char letter : puzzle.get_alphabet()) {
        if (puzzle.find_char_from_substitution_vector(letter) == -1) {
            letter_str = "";
            letter_str += letter;
            std::cout << uppercase(letter_str) << "  ";
        }
    }
    std::cout << std::endl;
}

void PuzzleCLI::print_codeword_progress() {
    print_codeword_progress(puzzle.get_codewords());
}

void PuzzleCLI::print_codeword_progress(std::vector<std::vector<int>> codewords_here) {
    int actual_index, num_of_matched_words;
    std::string word, codeword_str, part1, part2, part3, part4;
    for (std::vector<int> codeword : codewords_here) {
        actual_index = puzzle.get_codeword_index(codeword);
        word = puzzle.get_decrypted_codeword(codeword);
        codeword_str = codeword_as_str(codeword);
        num_of_matched_words = puzzle.get_num_of_matched_words(actual_index);
        part1 = add_whitespace(std::to_string(actual_index + 1), puzzle.max_num_size);
        part2 = uppercase(add_whitespace(word, puzzle.max_word_length));
        part3 = add_whitespace(codeword_str, puzzle.max_codeword_str_length);
        part4 = mass_replace(current_language_map["matching_words_text"], {std::to_string(num_of_matched_words)});
        std::cout << part1 << " " << part2 << "    " << part3 << "    " << part4 << std::endl;
    }
}

void PuzzleCLI::choose_progress_to_show() {
    int default_option = 1;
    std::vector<std::string> options = {current_language_map["show_unsolved_text"], current_language_map["show_all_text"], current_language_map["show_solved_text"]};

    std::cout << mass_replace(current_language_map["choose_progress_shown_text"], {std::to_string(default_option)}) << std::endl;;
    int ordinal;
    for (int i = 0; i < options.size(); i++) {
        ordinal = i + 1;
        std::cout << add_whitespace(std::to_string(ordinal), 3) << " " << options[i] << std::endl;
    }
    std::string input_string;
    int choice;
    std::getline(std::cin, input_string);
    try
    {
        choice = std::stoi(input_string);
    }
    catch(const std::invalid_argument& e)
    {
        choice = default_option;
    }

    if (choice == 2) {
        print_codeword_progress();
        return;
    }

    std::vector<std::vector<int>> codewords_to_show;

    if (choice == 3) {
        for (std::vector<int> codeword : puzzle.get_codewords()) {
            if (puzzle.is_codeword_solved(codeword)) {
                codewords_to_show.push_back(codeword);
            }
        }
        print_codeword_progress(codewords_to_show);
        return;
    }

    for (std::vector<int> codeword : puzzle.get_codewords()) {
        if (!puzzle.is_codeword_solved(codeword)) {
            codewords_to_show.push_back(codeword);
        }
    }
    print_codeword_progress(codewords_to_show);
}

void PuzzleCLI::show_matching_words() {
    std::vector<int> the_codeword;

    std::cout << current_language_map["codeword_prompt"];
    std::string codeword_input;
    std::getline(std::cin, codeword_input);

    if (codeword_input == "") {
        the_codeword = puzzle.find_codeword_with_least_matches();
    }
    else {
        the_codeword = puzzle.find_codeword(codeword_input);
    }

    if (the_codeword.empty()) {
        std::cout << mass_replace(current_language_map["invalid_codeword_text"], {codeword_input}) << std::endl;
        return;
    }

    int index_to_show = puzzle.get_codeword_index(the_codeword) + 1;
    std::vector<std::string> words = puzzle.get_matched_words_for_codeword(index_to_show - 1);
    std::string codeword_str = codeword_as_str(the_codeword);
    std::cout << mass_replace(current_language_map["words_matching_codeword_text"], {std::to_string(words.size()), std::to_string(index_to_show), codeword_str}) << std::endl;
    
    for (std::string word : words) {
        std::cout << uppercase(word) << std::endl;
    }
}

void PuzzleCLI::choose_main_choice() {
    std::cout << std::endl;
    print_substitution_vector();
    std::cout << std::endl;

    // std::function<void()> func = std::bind(&PuzzleCLI::add_to_substitution_vector, *this);
    // PuzzleCLI&

    std::vector<std::pair<std::string, std::function<void(PuzzleCLI&)>>> choices = {
        std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["set_number_letter"], add_to_substitution_vector),
        std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["set_codeword_word"], set_codeword_as_word),
        std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["missing_letters"], print_missing_chars),
        std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["show_progress"], choose_progress_to_show),
        std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["show_matching_words"], show_matching_words),
        std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["find_unique_pairs"], find_unique_pairs),
        // std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["solve_with_steps"], try_to_solve_puzzle_with_steps),
        std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["solve_methodically"], try_to_solve_puzzle_fully_methodically),
        std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["restart"], restart),
        // std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["clear_screen"], clear_screen),
        std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["exit"], exit_program)
    };

    // std::vector<std::string> choices = {current_language_map["set_number_letter"], current_language_map["set_codeword_word"]};
    // choices.push_back(current_language_map["missing_letters"]);
    // choices.push_back(current_language_map["show_progress"]);
    // choices.push_back(current_language_map["show_matching_words"]);
    // choices.push_back(current_language_map["find_unique_pairs"]);
    // // choices.push_back(current_language_map["solve_with_steps"])
    // choices.push_back(current_language_map["solve_methodically"]);
    // choices.push_back(current_language_map["restart"]);
    // // choices.push_back(current_language_map["clear_screen"]);
    // choices.push_back(current_language_map["exit"]);

    std::cout << current_language_map["choose_action"] << std::endl;
    int ordinal;
    int num_of_choices = choices.size();
    for (int i = 0; i < num_of_choices; i++) {
        if (i == num_of_choices - 1) {
            ordinal = 0;
        }
        else {
            ordinal = i + 1;
        }
        std::cout << ordinal << "    " << choices[i].first << std::endl;
    }
    std::cout << std::endl;

    int choice_num = -1; 
    std::string input_string;
    
    while (choice_num < 0) {
        std::getline(std::cin, input_string);
        try
        {
            choice_num = std::stoi(input_string);
            if (choice_num >= 0 && choice_num < num_of_choices) {
                if (choice_num == 0) {
                    choice_num = num_of_choices - 1;
                }
                else {
                    choice_num--;
                }
                break;
            }
            else {
                choice_num = -1;
            }

        }
        catch(const std::invalid_argument& e)
        {
            if (lowercase(input_string) == "q") {
                choice_num = num_of_choices - 1;
            }
        }
        
    }

    choices[choice_num].second(*this);
    // choices[choice_num].second();

}
