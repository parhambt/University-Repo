#include "Questions.hpp"
#include "Exam.hpp"
#include "constants.hpp"
#include <algorithm>
#include <set>

Questions::Questions(std::string question_text, std::string difficulty, std::string subject,
                     std::string option1, std::string option2, std::string option3,
                     std::string option4, std::string correct_answer)
    : question_text(question_text), difficulty(difficulty), subject(subject),
      option1(option1), option2(option2), option3(option3), option4(option4),
      correct_answer(correct_answer), num_blanks(0), num_corrects(0), num_incorrect(0),
      priority(0), choosen_option(-1), num_seen_question(0) {
    all_questions[std::make_pair(subject, difficulty)].push_back(this);
    all_questions_vector.push_back(this);
}

std::vector<Questions*> Questions::get_questions_by_subject(std::string subject) {
    std::vector<Questions*> all_questions;
    for (auto difficulty : DIFFICULTY) {
        auto questions = Questions::all_questions[std::make_pair(subject, difficulty)];
        all_questions.insert(all_questions.end(), questions.begin(), questions.end());
    }
    return all_questions;
}

std::vector<std::string> Questions::find_all_subject() {
    std::set<std::string> all_subject;
    auto all_questions = Questions::all_questions;
    for (auto& [key, value] : all_questions) {
        all_subject.insert(key.first);
    }
    return std::vector(all_subject.begin(), all_subject.end());
}

std::string Questions::get_subject() {
    return this->subject;
}

std::vector<Questions*> Questions::choose_question_from_two_least_subject_avg() {
    std::vector<Questions*> choosen_questions;
    choosen_questions.reserve(10);
    auto subject_ratio_correctness = Questions::subject_ratio_correct_answer();
    auto sort_ratio = [](std::pair<std::string, double>& a, std::pair<std::string, double>& b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    };
    std::sort(subject_ratio_correctness.begin(), subject_ratio_correctness.end(), sort_ratio);
    std::string subject1 = subject_ratio_correctness[0].first, subject2 = subject_ratio_correctness[1].first;
    std::vector<std::vector<std::string>> template_exam = {{subject1, EASY, "3"}, {subject1, MEDIUM, "2"}, {subject1, HARD, "1"},
                                                           {subject2, EASY, "2"}, {subject2, MEDIUM, "1"}, {subject2, HARD, "1"}};
    choosen_questions = Questions::choose_question_by_priority(template_exam);
    return choosen_questions;
}

std::vector<std::pair<std::string, double>> Questions::subject_ratio_correct_answer() {
    std::vector<std::pair<std::string, double>> answer;
    std::vector<std::string> all_subject = Questions::find_all_subject();
    for (auto subject : all_subject) {
        int count_true = 0, all_seen_questions = 0;
        auto all_question_subject = get_questions_by_subject(subject);
        for (auto& question : all_question_subject) {
            if (question->choosen_option == std::stoi(question->correct_answer)) count_true++;
            all_seen_questions += question->num_seen_question;
        }
        answer.push_back({subject, all_seen_questions == 0 ? 0 : (double)count_true / all_seen_questions});
    }
    return answer;
}

std::map<std::pair<std::string, std::string>, std::vector<Questions*>>& Questions::get_all_questions() {
    return Questions::all_questions;
}

std::vector<Questions*> Questions::get_all_questions_vector() {
    return Questions::all_questions_vector;
}

std::vector<int> Questions::get_statistic_question() {
    return {this->num_corrects, this->num_incorrect, this->num_blanks};
}

int Questions::get_choosen_option() {
    return this->choosen_option;
}

std::string Questions::get_question_detail(std::string specific_part_question) {
    if (specific_part_question == "question_text") return this->question_text;
    else if (specific_part_question == "option1") return this->option1;
    else if (specific_part_question == "option2") return this->option2;
    else if (specific_part_question == "option3") return this->option3;
    else if (specific_part_question == "option4") return this->option4;
    else return "NONE";
}

bool Questions::evaluate_answer(std::string choosen_answer) {
    return this->correct_answer == choosen_answer;
}

bool Questions::look_like_proper_answer(std::string choosen_answer) {
    return (choosen_answer == "1" || choosen_answer == "2" || choosen_answer == "3" || choosen_answer == "4" || choosen_answer.empty());
}

void Questions::choose_answer_for_now(std::string choosen_answer) {
    if (choosen_answer == "1" || choosen_answer == "2" || choosen_answer == "3" || choosen_answer == "4") {
        this->choosen_option = std::stoi(choosen_answer);
    } else if (choosen_answer.empty()) {
        this->choosen_option = 0;
    }
}

std::map<std::string, std::vector<int>> Questions::add_subject(std::string exam_name) {
    std::map<std::string, std::vector<int>> initial_exam_statistics;
    auto all_subject = Questions::find_all_exam_subject(exam_name);
    for (auto subject : all_subject) {
        initial_exam_statistics.insert({subject, {0, 0, 0}});
    }
    return initial_exam_statistics;
}

void Questions::choose_answer(const std::pair<std::string, std::map<Questions*, std::string>>& questions_with_answer) {
    std::string exam_name = questions_with_answer.first;
    auto exam = Exam::get_exam(exam_name);
    std::map<std::string, std::vector<int>> temp_exam_statistics = Questions::add_subject(exam_name);
    for (const auto& [question, answer] : questions_with_answer.second) {
        std::string subject = question->get_subject();
        if (answer.empty()) question->choosen_option = 0;
        else question->choosen_option = std::stoi(answer);
        if (answer == question->correct_answer) {
            question->num_corrects += 1;
            temp_exam_statistics[subject][0] += 1;
        } else if (answer.empty()) {
            question->num_blanks += 1;
            temp_exam_statistics[subject][2] += 1;
        } else {
            question->num_incorrect += 1;
            temp_exam_statistics[subject][1] += 1;
        }
        question->priority_calculator();
        question->num_seen_question += 1;
    }
    exam->set_statistics_exam(temp_exam_statistics);
}

void Questions::priority_calculator() {
    int priority = 3 * (this->num_incorrect) + this->num_blanks - 2 * (this->num_corrects);
    this->priority = priority;
}

bool Questions::sort_priority(Questions* a, Questions* b) {
    if (a->priority != b->priority) return a->priority > b->priority;
    return a->question_text < b->question_text;
}

std::vector<Questions*> Questions::choose_question_by_priority(const std::vector<std::vector<std::string>>& template_exam) {
    std::vector<Questions*> choosen_questions;
    for (auto single_info_temp : template_exam) {
        std::string subject = single_info_temp[0], difficulty = single_info_temp[1];
        int count = std::stoi(single_info_temp[2]);
        std::vector<Questions*>& all_questions = Questions::get_all_questions()[std::make_pair(subject, difficulty)];
        std::sort(all_questions.begin(), all_questions.end(), Questions::sort_priority);
        std::vector<Questions*> choosen_question(all_questions.begin(), all_questions.begin() + count);
        choosen_questions.insert(choosen_questions.end(), choosen_question.begin(), choosen_question.end());
    }
    return choosen_questions;
}

std::map<std::string, std::vector<Questions*>> Questions::categoricalize_question_and_sort(const std::vector<Questions*>& exam_questions) {
    std::map<std::string, std::vector<Questions*>> categoricaled_question;
    for (auto question : exam_questions) {
        std::string subject = question->subject;
        categoricaled_question[subject].push_back(question);
    }
    for (auto& [key, value] : categoricaled_question) {
        std::sort(value.begin(), value.end(), [](Questions* a, Questions* b) {
            return a->question_text < b->question_text;
        });
    }
    return categoricaled_question;
}

std::vector<std::string> Questions::find_all_exam_subject(std::string exam_name) {
    auto exam = Exam::get_exam(exam_name);
    auto questions = exam->get_exams_questions();
    std::set<std::string> all_subject;
    for (auto question : questions) {
        all_subject.insert(question->get_subject());
    }
    return std::vector(all_subject.begin(), all_subject.end());
}