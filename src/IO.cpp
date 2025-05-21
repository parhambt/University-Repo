#include "IO.hpp"
#include "constants.hpp"
#include "Report.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>

void IO::input_handelling() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream current_line(line);
        std::string input;
        current_line >> input;
        if (input == CREATE_TEMP) {
            std::string template_name = IO::parse_word_in_quote(current_line);
            if (Exam::get_template_exam(template_name) == NONE_VECTOR) {
                Exam::add_template({{template_name, parse_template_data(current_line)}});
                std::cout << "Template \'" << template_name << "\' was created successfully.\n";
            } else {
                std::cout << "Duplicate name: \'" << template_name << "\'" << std::endl;
            }
        } else if (input == GENERATE_TEST) {
            std::string exam_name = IO::parse_word_in_quote(current_line);
            std::string template_name = IO::parse_word_in_quote(current_line);
            auto template_exam = Exam::get_template_exam(template_name);
            if (template_exam == NONE_VECTOR)
                std::cout << "Could not find template: \'" << template_name << "\'" << std::endl;
            else {
                std::vector<Questions*> exam_questions = Questions::choose_question_by_priority(template_exam);
                new Exam(exam_questions, exam_name);
                std::cout << "Test \'" << exam_name << "\' was generated successfully.\n";
            }
        } else if (input == ATTEND) {
            std::string test_name = parse_word_in_quote(current_line);
            Exam* exam = Exam::get_exam(test_name);
            if (exam == nullptr)
                std::cout << "Could not find test: \'" << test_name << "\'\n";
            else {
                Exam::add_exam_attends(exam);
                std::vector<Questions*> exam_questions = exam->get_exams_questions();
                auto categoricaled_question = Questions::categoricalize_question_and_sort(exam_questions);
                IO::print_exam(categoricaled_question, test_name);
            }
        } else if (input == AUTO_GENERATE) {
            std::string test_name = IO::parse_word_in_quote(current_line);
            auto exam_questions = Questions::choose_question_from_two_least_subject_avg();
            new Exam(exam_questions, test_name);
            std::cout << "Test \'" << test_name << "\' was generated successfully.\n";
        } else if (input == REPORT) {
            std::string next_input;
            current_line >> next_input;
            if (next_input == ALL) {
                IO::print_report(0, ALL);
            } else if (next_input == TEST) {
                std::string test_name = IO::parse_word_in_quote(current_line);
                IO::print_test(test_name);
            } else if (next_input == TESTS) {
                IO::report_tests();
            } else if (next_input == SUBJECT) {
                std::string subject_name;
                current_line >> subject_name;
                IO::report_subject(subject_name);
            }
        }
    }
}

std::string IO::capitalize_first_letter(std::string s) {
    if (!s.empty()) s[0] = std::toupper(s[0]);
    return s;
}

void IO::report_subject(std::string subject) {
    std::cout << "Results for " << subject << ":\n\n";
    std::vector<Questions*> all_questions;
    for (auto difficulty : DIFFICULTY) {
        auto questions = Questions::get_all_questions()[std::make_pair(subject, difficulty)];
        all_questions.reserve(questions.size());
        all_questions.insert(all_questions.end(), questions.begin(), questions.end());
        auto statistics = Report::report_statistics(questions);
        print_static(statistics, IO::capitalize_first_letter(difficulty), false);
    }
    auto all_statistic = Report::report_statistics(all_questions);
    std::string total_score = three_figure(Report::calculate_score(all_statistic));
    std::cout << "\nTotal score: " << total_score << ".\n";
}

void IO::print_report(int stage, std::string test_name) {
    if (stage == 0) std::cout << "Total report:\n\n";
    else std::cout << "Results for " << test_name << ":\n";
    std::map<std::string, std::vector<int>> statistics;
    if (stage == 0) statistics = Report::report_statistics_categorical(Questions::get_all_questions_vector());
    else {
        auto exam = Exam::get_exam(test_name);
        auto exam_questions = exam->get_exams_questions();
        statistics = Report::report_statistics_categorical(exam_questions);
    }
    for (auto [key, statistic] : statistics) {
        if (key == "total") continue;
        IO::print_static(statistic, key, true);
    }
    std::cout << "\nTotal results: " << statistics["total"][0] << " corrects, " << statistics["total"][1] << " incorrects and " << statistics["total"][2] << " blanks.\n";
    std::string total_score = three_figure(Report::calculate_score(statistics["total"]));
    std::cout << "Total score: " << total_score << ".\n";
}

void IO::print_test(std::string test_name) {
    std::cout << "Results for " << test_name << ":\n\n";
    auto exam = Exam::get_exam(test_name);
    auto statistics = exam->get_statistics_exam();
    std::vector<int> all_statistics = {0, 0, 0};
    for (const auto& [subject, statistic] : statistics) {
        std::string score = three_figure(Report::calculate_score(statistic));
        std::cout << subject << ": " << statistic[0] << " corrects, " << statistic[1] << " incorrects and " << statistic[2] << " blanks. Score: " << score << ".\n";
        all_statistics[0] += statistic[0];
        all_statistics[1] += statistic[1];
        all_statistics[2] += statistic[2];
    }
    std::cout << "\nTotal results: " << all_statistics[0] << " corrects, " << all_statistics[1] << " incorrects and " << all_statistics[2] << " blanks.\n";
    std::string total_score = three_figure(Report::calculate_score(all_statistics));
    std::cout << "Total score: " << total_score << ".\n";
}

void IO::print_static(const std::vector<int>& statistic, std::string key, bool is_score) {
    if (is_score) {
        std::string score = three_figure(Report::calculate_score(statistic));
        std::cout << key << ": " << statistic[0] << " corrects, " << statistic[1] << " incorrects and " << statistic[2] << " blanks. Score: " << score << ".\n";
    } else {
        std::cout << key << ": " << statistic[0] << " corrects, " << statistic[1] << " incorrects and " << statistic[2] << " blanks.\n";
    }
}

void IO::report_tests() {
    std::cout << "Results per attended tests:\n\n";
    auto exams = Exam::get_exams_attends();
    for (auto& exam : exams) {
        std::string exam_name = exam->get_exam_name();
        auto exam_statistics = Exam::get_statistics_exam(exam);
        std::vector<int> statistics = {0, 0, 0};
        for (const auto& [subject, statistic] : exam_statistics) {
            statistics[0] += statistic[0];
            statistics[1] += statistic[1];
            statistics[2] += statistic[2];
        }
        std::string score = three_figure(Report::calculate_score(statistics));
        std::cout << exam_name << ": " << statistics[0] << " corrects, " << statistics[1] << " incorrects and " << statistics[2] << " blanks. Score:" << score << ".\n";
    }
}

std::string IO::three_figure(double value) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(3) << (value * 100) << "%";
    return out.str();
}

void IO::print_exam(const std::map<std::string, std::vector<Questions*>>& categoricaled_question, std::string test_name) {
    std::pair<std::string, std::map<Questions*, std::string>> questions_with_answer;
    questions_with_answer.first = test_name;
    std::cout << test_name << ":\n\n";
    int count = 1, count_prev = 0;
    std::vector<Questions*> questions_vector = Exam::map_to_vector(categoricaled_question);
    auto it = questions_vector.begin();
    while (it != questions_vector.end()) {
        bool is_valid_option = false;
        int choosen_answer = (*it)->get_choosen_option();
        if (!is_valid_option) {
            IO::option_printer(choosen_answer, it, count, count_prev);
        }
        bool state = IO::enter_option(it, is_valid_option, questions_vector, questions_with_answer);
        if (!state) {
            --it;
            --count;
            ++count_prev;
        } else {
            ++it;
            ++count;
            if (count_prev <= 0) count_prev = 0;
            else --count_prev;
        }
    }
    Questions::choose_answer(questions_with_answer);
    std::cout << "Finished " << test_name << ".\n";
}

void IO::option_printer(int choosen_answer, const std::vector<Questions*>::iterator it, int count, int count_prev) {
    std::cout << count << ") " << (*it)->get_question_detail(QUESTION_TEXT) << std::endl;
    if (choosen_answer == 1 && count_prev > 0)
        std::cout << TAB << "1. " << (*it)->get_question_detail(OPTION1) << FLASH << std::endl;
    else
        std::cout << TAB << "1. " << (*it)->get_question_detail(OPTION1) << std::endl;
    if (choosen_answer == 2 && count_prev > 0)
        std::cout << TAB << "2. " << (*it)->get_question_detail(OPTION2) << FLASH << std::endl;
    else
        std::cout << TAB << "2. " << (*it)->get_question_detail(OPTION2) << std::endl;
    if (choosen_answer == 3 && count_prev > 0)
        std::cout << TAB << "3. " << (*it)->get_question_detail(OPTION3) << FLASH << std::endl;
    else
        std::cout << TAB << "3. " << (*it)->get_question_detail(OPTION3) << std::endl;
    if (choosen_answer == 4 && count_prev > 0)
        std::cout << TAB << "4. " << (*it)->get_question_detail(OPTION4) << FLASH << std::endl;
    else
        std::cout << TAB << "4. " << (*it)->get_question_detail(OPTION4) << std::endl;
}

bool IO::enter_option(std::vector<Questions*>::iterator& it, bool& is_valid_option, std::vector<Questions*>& questions, std::pair<std::string, std::map<Questions*, std::string>>& questions_with_answer) {
    while (!is_valid_option) {
        std::string answer;
        std::cout << "Your answer: ";
        std::getline(std::cin, answer);
        is_valid_option = Questions::look_like_proper_answer(answer);
        (*it)->choose_answer_for_now(answer);
        if (is_valid_option) questions_with_answer.second.insert_or_assign((*it), answer);
        if (answer == "previous" && questions.begin() != it) return false;
        else if (answer == "previous" && questions.begin() == it) is_valid_option = false;
        if (!is_valid_option) std::cout << "Invalid answer, please try again.\n";
    }
    return true;
}

std::vector<std::vector<std::string>> IO::parse_template_data(std::istringstream& given_line) {
    std::string single_data;
    std::vector<std::vector<std::string>> parsed_data;
    while (std::getline(given_line, single_data, ' ')) {
        std::istringstream exam_detail(single_data);
        std::string subj, difficulty, count;
        std::getline(exam_detail, subj, ':');
        std::getline(exam_detail, difficulty, ':');
        std::getline(exam_detail, count, ' ');
        parsed_data.push_back({subj, difficulty, count});
    }
    return parsed_data;
}

std::string IO::parse_word_in_quote(std::istringstream& given_line) {
    std::string target_word;
    char single_quote;
    given_line >> std::ws >> single_quote;
    std::getline(given_line, target_word, '\'');
    given_line >> std::ws;
    return target_word;
}