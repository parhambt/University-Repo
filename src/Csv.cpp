#include "Csv.hpp"
#include "Questions.hpp"
#include <fstream>
#include <sstream>

Csv::Csv(std::string path) : path(path) {}

void Csv::parsing_csv() {
    std::ifstream csv(this->path);
    std::string line;
    std::getline(csv, line);
    while (std::getline(csv, line)) {
        Csv::parse_line_csv(line);
    }
}

void Csv::parse_line_csv(std::string line) {
    std::istringstream current_line(line);
    std::string question_text, option1, option2, option3, option4, correct_answer, difficulty, subject;
    std::getline(current_line, question_text, ',');
    std::getline(current_line, option1, ',');
    std::getline(current_line, option2, ',');
    std::getline(current_line, option3, ',');
    std::getline(current_line, option4, ',');
    std::getline(current_line, correct_answer, ',');
    std::getline(current_line, difficulty, ',');
    std::getline(current_line, subject);
    new Questions(question_text, difficulty, subject, option1, option2, option3, option4, correct_answer);
}