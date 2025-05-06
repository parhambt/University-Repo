#ifndef EXAM_HPP
#define EXAM_HPP

#include <vector>
#include <map>
#include <string>
#include "Questions.hpp"

class Exam {
private:
    std::vector<Questions*> exam_questions;
    std::string exam_name;
    std::map<std::string, std::vector<int>> exam_statistics;
    inline static std::map<std::string, std::vector<std::vector<std::string>>> templates_exam = {};
    inline static std::map<std::string, Exam*> all_exams = {};
    inline static std::vector<Exam*> all_exams_attend = {};

public:
    Exam(std::vector<Questions*> exam_questions, std::string exam_name);
    void set_statistics_exam(const std::map<std::string, std::vector<int>>& exam_statistics);
    static std::map<std::string, std::vector<int>> get_statistics_exam(Exam* exam);
    std::map<std::string, std::vector<int>> get_statistics_exam();
    static void add_template(const std::map<std::string, std::vector<std::vector<std::string>>>& template_exam);
    static std::vector<std::vector<std::string>> get_template_exam(std::string template_name);
    static Exam* get_exam(std::string exam_name);
    std::vector<Questions*> get_exams_questions();
    static void add_exam_attends(Exam* exam);
    static std::vector<Exam*> get_exams_attends();
    std::string get_exam_name();
    static std::vector<Questions*> map_to_vector(const std::map<std::string, std::vector<Questions*>>& all_questions);
};

#endif 