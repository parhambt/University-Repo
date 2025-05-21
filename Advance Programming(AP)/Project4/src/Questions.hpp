#ifndef QUESTIONS_HPP
#define QUESTIONS_HPP

#include <vector>
#include <map>
#include <string>
#include <utility>

class Exam;

class Questions {
private:
    int num_blanks, num_corrects, num_incorrect, priority, choosen_option, num_seen_question;
    std::string question_text, difficulty, subject, option1, option2, option3, option4, correct_answer;
    inline static std::map<std::pair<std::string, std::string>, std::vector<Questions*>> all_questions = {};
    inline static std::vector<Questions*> all_questions_vector = {};

public:
    Questions(std::string question_text, std::string difficulty, std::string subject,
              std::string option1, std::string option2, std::string option3,
              std::string option4, std::string correct_answer);
    static std::vector<Questions*> get_questions_by_subject(std::string subject);
    static std::vector<std::string> find_all_subject();
    std::string get_subject();
    static std::vector<Questions*> choose_question_from_two_least_subject_avg();
    static std::vector<std::pair<std::string, double>> subject_ratio_correct_answer();
    static std::map<std::pair<std::string, std::string>, std::vector<Questions*>>& get_all_questions();
    static std::vector<Questions*> get_all_questions_vector();
    std::vector<int> get_statistic_question();
    int get_choosen_option();
    std::string get_question_detail(std::string specific_part_question);
    bool evaluate_answer(std::string choosen_answer);
    static bool look_like_proper_answer(std::string choosen_answer);
    void choose_answer_for_now(std::string choosen_answer);
    static std::map<std::string, std::vector<int>> add_subject(std::string exam_name);
    static void choose_answer(const std::pair<std::string, std::map<Questions*, std::string>>& questions_with_answer);
    void priority_calculator();
    static bool sort_priority(Questions* a, Questions* b);
    static std::vector<Questions*> choose_question_by_priority(const std::vector<std::vector<std::string>>& template_exam);
    static std::map<std::string, std::vector<Questions*>> categoricalize_question_and_sort(const std::vector<Questions*>& exam_questions);
    static std::vector<std::string> find_all_exam_subject(std::string exam_name);
};

#endif 