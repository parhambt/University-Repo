#ifndef IO_HPP
#define IO_HPP

#include <string>
#include <vector>
#include <map>
#include "Questions.hpp"
#include "Exam.hpp"

class IO {
public:
    static void input_handelling();
    static std::string capitalize_first_letter(std::string s);
    static void report_subject(std::string subject);
    static void print_report(int stage, std::string test_name);
    static void print_test(std::string test_name);
    static void print_static(const std::vector<int>& statistic, std::string key, bool is_score);
    static void report_tests();
    static std::string three_figure(double value);
    static void print_exam(const std::map<std::string, std::vector<Questions*>>& categoricaled_question, std::string test_name);
    static void option_printer(int choosen_answer, const std::vector<Questions*>::iterator it, int count, int count_prev);
    static bool enter_option(std::vector<Questions*>::iterator& it, bool& is_valid_option, std::vector<Questions*>& questions, std::pair<std::string, std::map<Questions*, std::string>>& questions_with_answer);
    static std::vector<std::vector<std::string>> parse_template_data(std::istringstream& given_line);
    static std::string parse_word_in_quote(std::istringstream& given_line);
};

#endif 