
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

    alphabet = utf8_split(config[language][ALPHABET_KEY]);
    alphabet_upper = utf8_split(config[language][ALPHABET_UPPER_KEY]);
}

PuzzleCLI::~PuzzleCLI() {

}

// void PuzzleCLI::CallSelectedFunction(MemberFuncPtr func) {
//     (this->*func)();
// }

std::pair<char, char> PuzzleCLI::get_yes_no_pair() {
    return std::pair<char, char>(current_language_map["yes"][0], current_language_map["no"][0]);
}

bool PuzzleCLI::yes_no_question(std::string question_text) {
    std::pair<char, char> yes_no_pair = get_yes_no_pair();
    std::string help_text = current_language_map["help_text"];
    return yes_or_no_question(question_text, yes_no_pair, help_text);
}

std::string PuzzleCLI::to_upper(std::string text) {
    std::vector<std::string> text_vector = utf8_split(text);
    return to_upper(text_vector);
}
    
std::string PuzzleCLI::to_lower(std::string text) {
    std::vector<std::string> text_vector = utf8_split(text);
    return to_lower(text_vector);
}
    
std::string PuzzleCLI::to_upper(std::vector<std::string> text_vector) {
    std::string result_text = "";
    int index;
    for (std::string text : text_vector) {
        index = find(alphabet, text);
        if (index > -1) {
            result_text += alphabet_upper[index];
            continue;
        }
        result_text += text;
    }

    return result_text;
}
    
std::string PuzzleCLI::to_lower(std::vector<std::string> text_vector) {
    std::string result_text = "";
    int index;
    for (std::string text : text_vector) {
        index = find(alphabet_upper, text);
        if (index > -1) {
            result_text += alphabet[index];
            continue;
        }
        result_text += text;
    }

    return result_text;
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
    // std::string alphabet = config[language][ALPHABET_KEY];
    std::vector<std::string> alphabet = utf8_split(config[language][ALPHABET_KEY]);
    for (std::string letter : utf8_split(config[language][ALPHABET_UPPER_KEY])) {
        alphabet.push_back(letter);
    }
    if (the_wordlist_path == "") {
        wordlist_path = config[language][WORDLIST_PATH_KEY];
    }
    // std::vector<std::string> full_wordlist = get_wordlist(wordlist_path);
    std::vector<std::vector<std::string>> full_wordlist = get_wordlist_vector(wordlist_path);
    std::vector<std::vector<std::string>> wordlist;
    for (std::vector<std::string> word_vector : full_wordlist) {
        if (are_letters_in_alphabet(word_vector, alphabet)) {
            wordlist.push_back(word_vector);
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
    std::vector<std::string> letters;

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
        if (letter == "") {
            letters.push_back(letter);
            continue;
        }
        letter = utf8_split(letter)[0];
        // TODO: try-catch here?
        // letters.push_back(tolower(letter[0]));
        letters.push_back(letter);
    }

    if (numbers.size() != letters.size()) {
        // TODO: message here?
        return;
    }

    int issue, num_already;
    std::string text_to_show;
    for (int i = 0; i < numbers.size(); i++) {
        // issue = puzzle.add_to_substitution_vector(numbers[i], letters[i], issues, false);
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
            text_to_show = mass_replace(current_language_map["not_in_alphabet_text"], {letters[i], join_string(puzzle.get_alphabet(), "")});
            std::cout << text_to_show << std::endl;
            continue;
        }

        if (issue == 3) {
            num_already = puzzle.find_char_from_substitution_vector(letters[i]);
            text_to_show = mass_replace(current_language_map["already_in_table_text"], {letters[i], std::to_string(num_already)});
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
        puzzle.add_to_substitution_vector(the_codeword[i], word_input.substr(i, 1), issues, true);
    }
    // puzzle.set_matched_words();
}
    
void PuzzleCLI::print_pairs(CodewordWordPair codeword_word_pair) {
    std::vector<int> codeword1 = codeword_word_pair.codeword1;
    std::vector<int> codeword2 = codeword_word_pair.codeword2;
    // THIS IS BAD
    std::string word1 = join_string(codeword_word_pair.word1, "");
    std::string word2 = join_string(codeword_word_pair.word2, "");

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

    std::string part1 = add_whitespace(utf8_split(std::to_string(codeword_index1)), puzzle.max_num_size);
    part1 += " ";
    part1 += add_whitespace(utf8_split(codeword1_str), puzzle.max_codeword_str_length);

    std::string part2 = add_whitespace(utf8_split(std::to_string(codeword_index2)), puzzle.max_num_size);
    part1 += " ";
    part1 += add_whitespace(utf8_split(codeword2_str), puzzle.max_codeword_str_length);

    std::string part3 = to_upper(add_whitespace(utf8_split(word1), puzzle.max_word_length));
    std::string part4 = to_upper(add_whitespace(utf8_split(word2), puzzle.max_word_length));

    std::cout << part1 << "   " << part2 << "   " << part3 << "  " << part4 << std::endl; 
}

// std::vector<CodewordWordPair> PuzzleCLI::find_unique_pairs() {
void PuzzleCLI::find_unique_pairs() {
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
    // return unique_pairs;
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
        std::string part1 = add_whitespace(utf8_split(std::to_string(found_words)), puzzle.max_num_size);
        std::string part2 = current_language_map["best_match_text"];
        std::string part3 = add_whitespace(utf8_split(std::to_string(optimal_pair.first + 1)), puzzle.max_num_size);
        std::string part4 = add_whitespace(utf8_split(codeword_str), puzzle.max_codeword_str_length);
        std::string part5 = to_upper(add_whitespace(utf8_split(optimal_pair.second), puzzle.max_word_length));
        std::cout << part1 << " " << part2 << part3 << "  " << part4 << "  " << part5 << std::endl;
        
        // puzzle.set_codeword_to_word(optimal_pair.first, optimal_pair.second);
        puzzle.set_codeword_to_word(optimal_pair.first, utf8_split(optimal_pair.second));
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
        std::cout << to_upper(line) << std::endl;
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
    // std::string alphabet = puzzle.get_alphabet();
    std::vector<std::string> alphabet = puzzle.get_alphabet();
    for (int i = 0; i < alphabet.size(); i++) {
        letter_str = alphabet[i];
        if (puzzle.find_char_from_substitution_vector(letter_str) == -1) {
            // letter_str = "";
            // letter_str += letter;
            std::cout << to_upper(letter_str) << "  ";
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
        part1 = add_whitespace(utf8_split(std::to_string(actual_index + 1)), puzzle.max_num_size);
        part2 = to_upper(add_whitespace(utf8_split(word), puzzle.max_word_length));
        part3 = add_whitespace(utf8_split(codeword_str), puzzle.max_codeword_str_length);
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
        std::cout << add_whitespace(utf8_split(std::to_string(ordinal)), 3) << " " << options[i] << std::endl;
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
    // std::vector<std::string> words = puzzle.get_matched_words_for_codeword(index_to_show - 1);
    std::vector<std::vector<std::string>> words = puzzle.get_matched_words_for_codeword(index_to_show - 1);
    std::string codeword_str = codeword_as_str(the_codeword);
    std::cout << mass_replace(current_language_map["words_matching_codeword_text"], {std::to_string(words.size()), std::to_string(index_to_show), codeword_str}) << std::endl;
    
    for (std::vector<std::string> word_vector : words) {
        std::cout << to_upper(join_string(word_vector, "")) << std::endl;
    }
}

void PuzzleCLI::choose_main_choice() {
    std::cout << std::endl;
    print_substitution_vector();
    std::cout << std::endl;

    MemberFuncPtr func = &PuzzleCLI::add_to_substitution_vector;

    std::vector<std::string> descriptions = {current_language_map["set_number_letter"]};
    std::vector<MemberFuncPtr> funcs = {&PuzzleCLI::add_to_substitution_vector};

    descriptions.push_back(current_language_map["set_codeword_word"]);
    funcs.push_back(&PuzzleCLI::set_codeword_as_word);

    descriptions.push_back(current_language_map["missing_letters"]);
    funcs.push_back(&PuzzleCLI::print_missing_chars);

    descriptions.push_back(current_language_map["show_progress"]);
    funcs.push_back(&PuzzleCLI::choose_progress_to_show);

    descriptions.push_back(current_language_map["show_matching_words"]);
    funcs.push_back(&PuzzleCLI::show_matching_words);

    descriptions.push_back(current_language_map["find_unique_pairs"]);
    funcs.push_back(&PuzzleCLI::find_unique_pairs);

    // descriptions.push_back(current_language_map["solve_with_steps"]);
    // funcs.push_back(&PuzzleCLI::try_to_solve_puzzle_with_steps);

    descriptions.push_back(current_language_map["solve_methodically"]);
    funcs.push_back(&PuzzleCLI::try_to_solve_puzzle_fully_methodically);

    descriptions.push_back(current_language_map["restart"]);
    funcs.push_back(&PuzzleCLI::restart);

    // descriptions.push_back(current_language_map["clear_screen"]);
    // funcs.push_back(&PuzzleCLI::clear_screen);

    descriptions.push_back(current_language_map["exit"]);
    funcs.push_back(&PuzzleCLI::exit_program);

    // std::function<void()> func = std::bind(&PuzzleCLI::add_to_substitution_vector, *this);
    // PuzzleCLI&

    // std::vector<std::pair<std::string, std::function<void(PuzzleCLI&)>>> choices = {
    //     std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["set_number_letter"], add_to_substitution_vector),
    //     std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["set_codeword_word"], set_codeword_as_word),
    //     std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["missing_letters"], print_missing_chars),
    //     std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["show_progress"], choose_progress_to_show),
    //     std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["show_matching_words"], show_matching_words),
    //     std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["find_unique_pairs"], find_unique_pairs),
    //     // std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["solve_with_steps"], try_to_solve_puzzle_with_steps),
    //     std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["solve_methodically"], try_to_solve_puzzle_fully_methodically),
    //     std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["restart"], restart),
    //     // std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["clear_screen"], clear_screen),
    //     std::pair<std::string, std::function<void(PuzzleCLI&)>>(current_language_map["exit"], exit_program)
    // };

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
    // int num_of_choices = choices.size();
    int num_of_choices = descriptions.size();
    for (int i = 0; i < num_of_choices; i++) {
        if (i == num_of_choices - 1) {
            ordinal = 0;
        }
        else {
            ordinal = i + 1;
        }
        // std::cout << ordinal << "    " << choices[i].first << std::endl;
        std::cout << ordinal << "    " << descriptions[i] << std::endl;
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

    (this->*funcs[choice_num])();
    // this->CallSelectedFunction(funcs[choice_num]);
    // choices[choice_num].second(*this);
    // choices[choice_num].second();

}




PuzzleCLI1::PuzzleCLI1() {
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

    alphabet = utf8_split(config[language][ALPHABET_KEY]);
    alphabet_upper = utf8_split(config[language][ALPHABET_UPPER_KEY]);
    alphabet_map = get_alphabet_map(config[language][ALPHABET_KEY]);
}

PuzzleCLI1::~PuzzleCLI1() {

}

// void PuzzleCLI1::CallSelectedFunction(MemberFuncPtr func) {
//     (this->*func)();
// }

std::pair<char, char> PuzzleCLI1::get_yes_no_pair() {
    return std::pair<char, char>(current_language_map["yes"][0], current_language_map["no"][0]);
}

bool PuzzleCLI1::yes_no_question(std::string question_text) {
    std::pair<char, char> yes_no_pair = get_yes_no_pair();
    std::string help_text = current_language_map["help_text"];
    return yes_or_no_question(question_text, yes_no_pair, help_text);
}

std::string PuzzleCLI1::to_upper(std::string text) {
    std::vector<std::string> text_vector = utf8_split(text);
    return to_upper(text_vector);
}
    
std::string PuzzleCLI1::to_lower(std::string text) {
    std::vector<std::string> text_vector = utf8_split(text);
    return to_lower(text_vector);
}
    
std::string PuzzleCLI1::to_upper(std::vector<std::string> text_vector) {
    std::string result_text = "";
    int index;
    for (std::string text : text_vector) {
        index = find(alphabet, text);
        if (index > -1) {
            result_text += alphabet_upper[index];
            continue;
        }
        result_text += text;
    }

    return result_text;
}
    
std::string PuzzleCLI1::to_lower(std::vector<std::string> text_vector) {
    std::string result_text = "";
    int index;
    for (std::string text : text_vector) {
        index = find(alphabet_upper, text);
        if (index > -1) {
            result_text += alphabet[index];
            continue;
        }
        result_text += text;
    }

    return result_text;
}

std::string PuzzleCLI1::to_upper_int(std::vector<int> text_vector) {
    std::vector<std::string> word_vector;
    for (int num : text_vector) {
        if (num == 0) {
            word_vector.push_back(empty_symbol);
            continue;
        }
        word_vector.push_back(alphabet_upper[num - 1]);
    }

    return to_upper(word_vector);
}

std::string PuzzleCLI1::to_lower_int(std::vector<int> text_vector) {
    std::vector<std::string> word_vector;
    for (int num : text_vector) {
        if (num == 0) {
            word_vector.push_back(empty_symbol);
            continue;
        }
        word_vector.push_back(alphabet[num - 1]);
    }

    return to_upper(word_vector);
}

std::string PuzzleCLI1::replace1(std::string text_key, std::string replacement_text) {
    return mass_replace(current_language_map[text_key], {replacement_text});
}

std::string PuzzleCLI1::replace2(std::string text_key, std::string replacement_text1, std::string replacement_text2) {
    return mass_replace(current_language_map[text_key], {replacement_text1, replacement_text2});
}

std::string PuzzleCLI1::replace3(std::string text_key, std::string replacement_text1, std::string replacement_text2, std::string replacement_text3) {
    return mass_replace(current_language_map[text_key], {replacement_text1, replacement_text2, replacement_text3});
}

void PuzzleCLI1::set_language(std::string new_language) {
    if (language_map.find(new_language) == language_map.end()) {
        language = default_language;
    }
    else {
        language = new_language;
        alphabet = utf8_split(config[language][ALPHABET_KEY]);
        alphabet_upper = utf8_split(config[language][ALPHABET_UPPER_KEY]);
        alphabet_map = get_alphabet_map(config[language][ALPHABET_KEY]);
    }
    current_language_map = language_map[language];
}

std::vector<std::string> PuzzleCLI1::get_languages() {
    std::vector<std::string> languages;
    for (auto item : config) {
        languages.push_back(item.first);
    }
    return languages;
}

void PuzzleCLI1::choose_language() {
    std::vector<std::string> languages = get_languages();
    std::string languages_str = languages[0];
    if (languages.size() > 1) {
        for (int i = 1; i < languages.size(); i++) {
            languages_str += ", ";
            languages_str += languages[i];
        }
    }

    // std::string choose_prompt = mass_replace(current_language_map["choose_language"], {languages_str});
    std::string choose_prompt = replace1("choose_language", languages_str);

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
            // std::string question_text = mass_replace(current_language_map["add_new_language_question"], {language_answer});
            std::string question_text = replace1("add_new_language_question", language_answer);
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

int PuzzleCLI1::choose_codeword_path() {
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
        // question_text = mass_replace(current_language_map["file_not_found_try_again"], {path_answer});
        question_text = replace1("file_not_found_try_again", path_answer);
        try_again = yes_no_question(question_text);
        if (!try_again) {
            return -1;
        }
    }
}

void PuzzleCLI1::initialize_puzzle(std::string the_codeword_path, std::string the_wordlist_path) {
    codeword_path = the_codeword_path;
    CodewordsAndComments comments_n_codewords = get_codewords_and_comments(codeword_path);
    // std::pair<std::vector<std::string>, std::vector<std::vector<int>>> comments_n_codewords = get_codewords(codeword_path);
    std::vector<std::string> comments = comments_n_codewords.comments;
    std::vector<std::vector<int>> codewords = comments_n_codewords.codewords;
    std::vector<int> codeword_lengths = comments_n_codewords.codeword_lengths;
    // std::string alphabet = config[language][ALPHABET_KEY];
    std::vector<std::string> alphabet = utf8_split(config[language][ALPHABET_KEY]);
    for (std::string letter : utf8_split(config[language][ALPHABET_UPPER_KEY])) {
        alphabet.push_back(letter);
    }
    if (the_wordlist_path == "") {
        wordlist_path = config[language][WORDLIST_PATH_KEY];
    }
    // std::vector<std::string> full_wordlist = get_wordlist(wordlist_path);
    std::pair<std::vector<int>, std::vector<std::vector<int>>> wordlist_stuff = get_wordlist_as_int_vector_plus(wordlist_path, alphabet_map);
    // std::vector<std::vector<std::string>> full_wordlist = get_wordlist_vector(wordlist_path);
    // std::vector<std::vector<std::string>> wordlist;
    // for (std::vector<std::string> word_vector : full_wordlist) {
    //     if (are_letters_in_alphabet(word_vector, alphabet)) {
    //         wordlist.push_back(word_vector);
    //     }
    // }

    puzzle = CodewordPuzzle1(comments_n_codewords.codewords, comments_n_codewords.codeword_lengths, wordlist_stuff.second, wordlist_stuff.first, alphabet.size(), comments_n_codewords.comments);

}
    
void PuzzleCLI1::input_data_and_initialize_puzzle(std::string the_language, std::string the_codeword_path) {
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

void PuzzleCLI1::restart() {
    puzzle.clear_substitution_vector();
}

void PuzzleCLI1::exit_program() {
    running = false;
}

std::pair<std::vector<int>, std::vector<int>> PuzzleCLI1::ask_for_numbers_and_letters() {
    std::vector<int> numbers;
    std::vector<int> letters;

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
            return std::pair<std::vector<int>, std::vector<int>>({}, {});
        }
    }

    std::cout << current_language_map["letter_prompt"];
    std::string letter_input;
    std::getline(std::cin, letter_input);
    std::vector<std::string> letter_input_split = split_string(letter_input, ',');
    for (std::string letter : letter_input_split) {
        letter = remove_whitespace(letter);
        if (letter == "") {
            letters.push_back(0);
            continue;
        }
        letter = utf8_split(letter)[0];
        // TODO: try-catch here?
        // letters.push_back(tolower(letter[0]));
        letters.push_back(alphabet_map[letter]);
    }

    if (numbers.size() != letters.size()) {
        // TODO: message here?
        return std::pair<std::vector<int>, std::vector<int>>({}, {});
    }


    return std::pair<std::vector<int>, std::vector<int>>(numbers, letters);
}

void PuzzleCLI1::add_to_substitution_vector() {

    std::pair<std::vector<int>, std::vector<int>> nums_and_letters = PuzzleCLI1::ask_for_numbers_and_letters();
    std::vector<int> numbers = nums_and_letters.first;
    std::vector<int> letters = nums_and_letters.second;

    if (numbers.empty()) {
        return;
    }

    int issue, num_already;
    std::string text_to_show;
    for (int i = 0; i < numbers.size(); i++) {
        // issue = puzzle.add_to_substitution_vector(numbers[i], letters[i], issues, false);
        issue = puzzle.add_to_substitution_vector(numbers[i], letters[i], issues, false);

        if (issue == 0) {
            // std::cout << "Added " << numbers[i] << " = " << letters[i] << std::endl;
            continue;
        }

        if (issue == 1) {
            // text_to_show = mass_replace(current_language_map["invalid_number_text"], {std::to_string(numbers[i])});
            text_to_show = replace1("invalid_number_text", std::to_string(numbers[i]));
            std::cout << text_to_show << std::endl;
            continue;
        }

        if (issue == 2) {
            // text_to_show = mass_replace(current_language_map["not_in_alphabet_text"], {letters[i], join_string(puzzle.get_alphabet(), "")});
            text_to_show = replace2("not_in_alphabet_text", alphabet[letters[i] - 1], join_string(alphabet, ""));
            std::cout << text_to_show << std::endl;
            continue;
        }

        if (issue == 3) {
            num_already = puzzle.get_substitution_vector_opp()[letters[i]];
            // num_already = puzzle.find_char_from_substitution_vector(letters[i]);
            // text_to_show = mass_replace(current_language_map["already_in_table_text"], {letters[i], std::to_string(num_already)});
            text_to_show = replace2("already_in_table_text", alphabet[letters[i] - 1], std::to_string(num_already));
            std::cout << text_to_show << std::endl;
        }
    }
    // print_substitution_vector();
}
    
void PuzzleCLI1::set_codeword_as_word() {

    std::cout << current_language_map["codeword_prompt"];
    std::string codeword_input;
    std::getline(std::cin, codeword_input);

    std::vector<int> the_codeword = puzzle.find_codeword(codeword_input);

    if (the_codeword.empty()) {
        // std::string invalid_codeword_text = mass_replace(current_language_map["invalid_codeword_text"], {codeword_input});
        std::string invalid_codeword_text = replace1("invalid_codeword_text", codeword_input);
        std::cout << invalid_codeword_text << std::endl;
        return;
    }

    std::cout << current_language_map["word_prompt"];
    std::string word_input;
    std::getline(std::cin, word_input);
    // MORE CHECKS NEEDED HERE!!!
    // word_input = lowercase(word_input);
    std::vector<std::string> word_input_vector = utf8_split(word_input);
    // word_input = to_lower(word_input_vector);

    if (!does_word_match(word_input_vector, the_codeword)) {
        // std::string no_match_text = mass_replace(current_language_map["no_match_text"], {word_input, codeword_as_str(the_codeword)});
        std::string no_match_text = replace2("no_match_text", word_input, codeword_as_str(the_codeword));
        std::cout << no_match_text << std::endl;
        return;
    }
    if (!are_letters_in_alphabet(word_input_vector, alphabet) && !are_letters_in_alphabet(word_input_vector, alphabet_upper)) {
        // THIS IS NOT THE CORRECT TEXT
        // text_to_show = replace2("not_in_alphabet_text", alphabet[letters[i] - 1], join_string(alphabet, ""));
        // text_to_show = replace2("letters_not_in_alphabet_text", word_input, join_string(alphabet, ""));
        // std::cout << text_to_show << std::endl;
        std::cout << replace2("letters_not_in_alphabet_text", word_input, join_string(alphabet, "")) << std::endl;
        return;
    }

    // TODO: is word in wordlist
    int letter_num;
    for (int i = 0; i < word_input_vector.size(); i++) {
        letter_num = alphabet_map[word_input_vector[i]];
        puzzle.add_to_substitution_vector(the_codeword[i], letter_num, issues, true);
    }
    // puzzle.set_matched_words();
}
    
void PuzzleCLI1::print_pairs(CodewordWordPair1 codeword_word_pair) {
    std::vector<int> codeword1 = codeword_word_pair.codeword1;
    std::vector<int> codeword2 = codeword_word_pair.codeword2;
    // THIS IS BAD
    std::vector<std::string> word_vector1, word_vector2;
    for (int num : codeword_word_pair.word1) {
        word_vector1.push_back(alphabet[num - 1]);
    }
    for (int num : codeword_word_pair.word2) {
        word_vector2.push_back(alphabet[num - 1]);
    }
    std::string word1 = join_string(word_vector1, "");
    std::string word2 = join_string(word_vector2, "");

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

    std::string part1 = add_whitespace(utf8_split(std::to_string(codeword_index1)), puzzle.max_num_size);
    part1 += " ";
    part1 += add_whitespace(utf8_split(codeword1_str), puzzle.max_codeword_str_length);

    std::string part2 = add_whitespace(utf8_split(std::to_string(codeword_index2)), puzzle.max_num_size);
    part1 += " ";
    part1 += add_whitespace(utf8_split(codeword2_str), puzzle.max_codeword_str_length);

    std::string part3 = to_upper(add_whitespace(utf8_split(word1), puzzle.max_word_length));
    std::string part4 = to_upper(add_whitespace(utf8_split(word2), puzzle.max_word_length));

    std::cout << part1 << "   " << part2 << "   " << part3 << "  " << part4 << std::endl; 
}

// std::vector<CodewordWordPair> PuzzleCLI1::find_unique_pairs() {
void PuzzleCLI1::find_unique_pairs() {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<CodewordWordPair1> unique_pairs = puzzle.find_all_unique_pairs();
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    double time_taken = duration.count() / 1000.0;
    // std::string unique_pairs_found_text = mass_replace(current_language_map["unique_pairs_found_text"], {std::to_string(unique_pairs.size()), std::to_string(time_taken)});
    std::string unique_pairs_found_text = replace2("unique_pairs_found_text", std::to_string(unique_pairs.size()), std::to_string(time_taken));
    std::cout << unique_pairs_found_text << std::endl;

    std::string solved_marker = "";
    solved_marker += solved_char;
    // std::cout << mass_replace(current_language_map["solved_words_note"], {solved_marker}) << std::endl;
    std::cout << replace1("solved_words_note", solved_marker) << std::endl;

    for (CodewordWordPair1 codeword_word_pair : unique_pairs) {
        print_pairs(codeword_word_pair);
    }
    // is return necessary?
    // return unique_pairs;
}

void PuzzleCLI1::print_solving_stats(double elapsed_time) {
    // std::cout << "\n" << mass_replace(current_language_map["solving_time_with_steps_text"], {std::to_string(elapsed_time)}) << std::endl;
    std::cout << "\n" << replace1("solving_time_with_steps_text", std::to_string(elapsed_time)) << std::endl;

    std::pair<int, int> word_counts = puzzle.count_solved_codewords();
    int num_of_solved_codewords = word_counts.first;
    int num_of_found_words = word_counts.second;
    // std::cout << mass_replace(current_language_map["found_codewords_text"], {std::to_string(num_of_solved_codewords), std::to_string(puzzle.num_of_codewords)}) << std::endl;
    std::cout << replace2("found_codewords_text", std::to_string(num_of_solved_codewords), std::to_string(puzzle.num_of_codewords)) << std::endl;
    // std::cout << mass_replace(current_language_map["found_codewords_in_wordlist_text"], {std::to_string(num_of_found_words)}) << std::endl;
    std::cout << replace1("found_codewords_in_wordlist_text", std::to_string(num_of_found_words)) << std::endl;

    int num_of_solved_numbers = puzzle.count_solved_numbers();
    // std::cout << mass_replace(current_language_map["substitution_table_decipher_text"], {std::to_string(num_of_solved_numbers), std::to_string(puzzle.num_of_letters)});
    std::cout << replace2("substitution_table_decipher_text", std::to_string(num_of_solved_numbers), std::to_string(puzzle.num_of_letters));
}

void PuzzleCLI1::try_to_solve_puzzle_fully_methodically() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
    try_to_solve_puzzle_methodically(start_time);
}

void PuzzleCLI1::try_to_solve_puzzle_methodically(std::chrono::time_point<std::chrono::high_resolution_clock> start_time) {
    int found_words = 0;

    std::pair<int, std::vector<int>> optimal_pair = puzzle.find_optimal_match();
    std::string the_word = "";
    while (optimal_pair.first > -1) {
        found_words++;

        the_word = "";
        for (int i = 0; i < optimal_pair.second.size(); i++) {
            the_word += alphabet[optimal_pair.second[i] - 1];
        }

        std::string codeword_str = codeword_as_str(puzzle.get_codewords()[optimal_pair.first]);
        std::string part1 = add_whitespace(utf8_split(std::to_string(found_words)), puzzle.max_num_size);
        std::string part2 = current_language_map["best_match_text"];
        std::string part3 = add_whitespace(utf8_split(std::to_string(optimal_pair.first + 1)), puzzle.max_num_size);
        std::string part4 = add_whitespace(utf8_split(codeword_str), puzzle.max_codeword_str_length);
        std::string part5 = to_upper(add_whitespace(the_word, puzzle.max_word_length));
        std::cout << part1 << " " << part2 << part3 << "  " << part4 << "  " << part5 << std::endl;
        
        // puzzle.set_codeword_to_word(optimal_pair.first, optimal_pair.second);
        puzzle.set_codeword_to_word(optimal_pair.first, optimal_pair.second);
        // puzzle.set_matched_words();

        optimal_pair = puzzle.find_optimal_match();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1000.0;
    print_solving_stats(elapsed_time);
}

void PuzzleCLI1::try_to_solve_puzzle_with_steps() {

}

void PuzzleCLI1::print_substitution_vector() {
    std::vector<int> subst_vect = puzzle.get_substitution_vector();

    std::string line1 = "";
    std::string line2 = "";
    std::string delimiter = " | ";
    std::string letter;
    for (int i = 1; i <= puzzle.num_of_letters; i++) {
        if (i > 1) {
            line1 += delimiter;
            line2 += delimiter;
        }
        line1 += std::to_string(i);
        letter = "";
        if (subst_vect[i] == puzzle.empty_num) {
            letter += ' ';
        }
        else {
            letter += alphabet_upper[subst_vect[i] - 1];
        }
        line2 += add_whitespace(utf8_split(letter), std::to_string(i).length());
    }
    std::cout << line1 << std::endl << line2 << std::endl;
}

void PuzzleCLI1::print_initial_info() {
    // std::cout << mass_replace(current_language_map["language"], {config[language]["name"]}) << std::endl;
    std::cout << replace1("language", config[language]["name"]) << std::endl;
    // std::cout << mass_replace(current_language_map["codewords_in_file"], {std::to_string(puzzle.num_of_codewords), codeword_path}) << std::endl;
    std::cout << replace2("codewords_in_file", std::to_string(puzzle.num_of_codewords), codeword_path) << std::endl;
    // std::cout << mass_replace(current_language_map["words_in_file"], {std::to_string(puzzle.num_of_words), wordlist_path}) << std::endl;
    std::cout << replace2("words_in_file", std::to_string(puzzle.num_of_words), wordlist_path) << std::endl;
    if (!puzzle.get_comments().empty()) {
        std::cout << current_language_map["comments"] << std::endl;
        for (std::string comment_line : puzzle.get_comments()) {
            std::cout << comment_line << std::endl;
        }
    }

}

void PuzzleCLI1::print_missing_chars() {
    std::cout << current_language_map["missing_letters_text"] << std::endl;
    std::string letter_str = "";
    // std::string alphabet = puzzle.get_alphabet();
    std::vector<int> subst_vect_opp = puzzle.get_substitution_vector_opp();
    // std::vector<std::string> alphabet = puzzle.get_alphabet();
    for (int i = 0; i < alphabet.size(); i++) {
        letter_str = alphabet[i];
        if (subst_vect_opp[i + 1] == puzzle.empty_num) {
            // letter_str = "";
            // letter_str += letter;
            std::cout << to_upper(letter_str) << "  ";
        }
    }
    std::cout << std::endl;
}

void PuzzleCLI1::print_codeword_progress() {
    print_codeword_progress(puzzle.get_codewords());
}

void PuzzleCLI1::print_codeword_progress(std::vector<std::vector<int>> codewords_here) {
    int actual_index, num_of_matched_words;
    std::string word, codeword_str, part1, part2, part3, part4;
    for (std::vector<int> codeword : codewords_here) {
        actual_index = puzzle.get_codeword_index(codeword);
        // std::cout << "actual index = " << actual_index << std::endl;
        word = to_upper_int(puzzle.get_decrypted_codeword(codeword));
        // std::cout << "word = " << word << std::endl;
        codeword_str = codeword_as_str(codeword);
        // std::cout << "codeword string = " << codeword_str << std::endl;
        num_of_matched_words = puzzle.get_num_of_matched_words(actual_index);
        part1 = add_whitespace(utf8_split(std::to_string(actual_index + 1)), puzzle.max_num_size);
        part2 = add_whitespace(word, puzzle.max_word_length);
        part3 = add_whitespace(utf8_split(codeword_str), puzzle.max_codeword_str_length);
        // part4 = mass_replace(current_language_map["matching_words_text"], {std::to_string(num_of_matched_words)});
        part4 = replace1("matching_words_text", std::to_string(num_of_matched_words));
        std::cout << part1 << " " << part2 << "    " << part3 << "    " << part4 << std::endl;
    }
}

void PuzzleCLI1::choose_progress_to_show() {
    int default_option = 1;
    std::vector<std::string> options = {current_language_map["show_unsolved_text"], current_language_map["show_all_text"], current_language_map["show_solved_text"]};

    // std::cout << mass_replace(current_language_map["choose_progress_shown_text"], {std::to_string(default_option)}) << std::endl;;
    std::cout << replace1("choose_progress_shown_text", std::to_string(default_option)) << std::endl;;
    int ordinal;
    for (int i = 0; i < options.size(); i++) {
        ordinal = i + 1;
        std::cout << add_whitespace(utf8_split(std::to_string(ordinal)), 3) << " " << options[i] << std::endl;
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

void PuzzleCLI1::show_matching_words() {
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
        // std::cout << mass_replace(current_language_map["invalid_codeword_text"], {codeword_input}) << std::endl;
        std::cout << replace1("invalid_codeword_text", codeword_input) << std::endl;
        return;
    }

    int index_to_show = puzzle.get_codeword_index(the_codeword) + 1;
    // std::vector<std::string> words = puzzle.get_matched_words_for_codeword(index_to_show - 1);
    std::vector<std::vector<int>> words = puzzle.get_matched_words_for_codeword(index_to_show - 1);
    std::string codeword_str = codeword_as_str(the_codeword);
    // std::cout << mass_replace(current_language_map["words_matching_codeword_text"], {std::to_string(words.size()), std::to_string(index_to_show), codeword_str}) << std::endl;
    std::cout << replace3("words_matching_codeword_text", std::to_string(words.size()), std::to_string(index_to_show), codeword_str) << std::endl;
    
    for (std::vector<int> word_vector : words) {
        std::cout << to_upper_int(word_vector) << std::endl;
    }
}

void PuzzleCLI1::choose_main_choice() {
    std::cout << std::endl;
    print_substitution_vector();
    std::cout << std::endl;

    MemberFuncPtr func = &PuzzleCLI1::add_to_substitution_vector;

    std::vector<std::string> descriptions = {current_language_map["set_number_letter"]};
    std::vector<MemberFuncPtr> funcs = {&PuzzleCLI1::add_to_substitution_vector};

    descriptions.push_back(current_language_map["set_codeword_word"]);
    funcs.push_back(&PuzzleCLI1::set_codeword_as_word);

    descriptions.push_back(current_language_map["missing_letters"]);
    funcs.push_back(&PuzzleCLI1::print_missing_chars);

    descriptions.push_back(current_language_map["show_progress"]);
    funcs.push_back(&PuzzleCLI1::choose_progress_to_show);

    descriptions.push_back(current_language_map["show_matching_words"]);
    funcs.push_back(&PuzzleCLI1::show_matching_words);

    descriptions.push_back(current_language_map["find_unique_pairs"]);
    funcs.push_back(&PuzzleCLI1::find_unique_pairs);

    // descriptions.push_back(current_language_map["solve_with_steps"]);
    // funcs.push_back(&PuzzleCLI1::try_to_solve_puzzle_with_steps);

    descriptions.push_back(current_language_map["solve_methodically"]);
    funcs.push_back(&PuzzleCLI1::try_to_solve_puzzle_fully_methodically);

    descriptions.push_back(current_language_map["restart"]);
    funcs.push_back(&PuzzleCLI1::restart);

    // descriptions.push_back(current_language_map["clear_screen"]);
    // funcs.push_back(&PuzzleCLI1::clear_screen);

    descriptions.push_back(current_language_map["exit"]);
    funcs.push_back(&PuzzleCLI1::exit_program);

    // std::function<void()> func = std::bind(&PuzzleCLI1::add_to_substitution_vector, *this);
    // PuzzleCLI1&

    // std::vector<std::pair<std::string, std::function<void(PuzzleCLI1&)>>> choices = {
    //     std::pair<std::string, std::function<void(PuzzleCLI1&)>>(current_language_map["set_number_letter"], add_to_substitution_vector),
    //     std::pair<std::string, std::function<void(PuzzleCLI1&)>>(current_language_map["set_codeword_word"], set_codeword_as_word),
    //     std::pair<std::string, std::function<void(PuzzleCLI1&)>>(current_language_map["missing_letters"], print_missing_chars),
    //     std::pair<std::string, std::function<void(PuzzleCLI1&)>>(current_language_map["show_progress"], choose_progress_to_show),
    //     std::pair<std::string, std::function<void(PuzzleCLI1&)>>(current_language_map["show_matching_words"], show_matching_words),
    //     std::pair<std::string, std::function<void(PuzzleCLI1&)>>(current_language_map["find_unique_pairs"], find_unique_pairs),
    //     // std::pair<std::string, std::function<void(PuzzleCLI1&)>>(current_language_map["solve_with_steps"], try_to_solve_puzzle_with_steps),
    //     std::pair<std::string, std::function<void(PuzzleCLI1&)>>(current_language_map["solve_methodically"], try_to_solve_puzzle_fully_methodically),
    //     std::pair<std::string, std::function<void(PuzzleCLI1&)>>(current_language_map["restart"], restart),
    //     // std::pair<std::string, std::function<void(PuzzleCLI1&)>>(current_language_map["clear_screen"], clear_screen),
    //     std::pair<std::string, std::function<void(PuzzleCLI1&)>>(current_language_map["exit"], exit_program)
    // };

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
    // int num_of_choices = choices.size();
    int num_of_choices = descriptions.size();
    for (int i = 0; i < num_of_choices; i++) {
        if (i == num_of_choices - 1) {
            ordinal = 0;
        }
        else {
            ordinal = i + 1;
        }
        // std::cout << ordinal << "    " << choices[i].first << std::endl;
        std::cout << ordinal << "    " << descriptions[i] << std::endl;
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

    (this->*funcs[choice_num])();
    // this->CallSelectedFunction(funcs[choice_num]);
    // choices[choice_num].second(*this);
    // choices[choice_num].second();

}