#include "Exam.hpp"
#include "constants.hpp"

Exam::Exam(std::vector<Questions*> exam_questions, std::string exam_name)
    : exam_questions(exam_questions), exam_name(exam_name) {
    all_exams.insert({exam_name, this});
    this->exam_statistics = {};
}

void Exam::set_statistics_exam(const std::map<std::string, std::vector<int>>& exam_statistics) {
    this->exam_statistics.insert(exam_statistics.begin(), exam_statistics.end());
}

std::map<std::string, std::vector<int>> Exam::get_statistics_exam(Exam* exam) {
    return exam->exam_statistics;
}

std::map<std::string, std::vector<int>> Exam::get_statistics_exam() {
    return this->exam_statistics;
}

void Exam::add_template(const std::map<std::string, std::vector<std::vector<std::string>>>& template_exam) {
    Exam::templates_exam.insert(*template_exam.begin());
}

std::vector<std::vector<std::string>> Exam::get_template_exam(std::string template_name) {
    if (Exam::templates_exam.find(template_name) != Exam::templates_exam.end())
        return Exam::templates_exam[template_name];
    else
        return NONE_VECTOR;
}

Exam* Exam::get_exam(std::string exam_name) {
    auto exam = Exam::all_exams.find(exam_name);
    if (exam == Exam::all_exams.end())
        return nullptr;
    return exam->second;
}

std::vector<Questions*> Exam::get_exams_questions() {
    return this->exam_questions;
}

void Exam::add_exam_attends(Exam* exam) {
    Exam::all_exams_attend.push_back(exam);
}

std::vector<Exam*> Exam::get_exams_attends() {
    return Exam::all_exams_attend;
}

std::string Exam::get_exam_name() {
    return this->exam_name;
}

std::vector<Questions*> Exam::map_to_vector(const std::map<std::string, std::vector<Questions*>>& all_questions) {
    std::vector<Questions*> vector;
    for (const auto& [key, questions] : all_questions) {
        for (const auto& question : questions) {
            vector.push_back(question);
        }
    }
    return vector;
}