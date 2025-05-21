#include "Report.hpp"

std::map<std::string, std::vector<int>> Report::report_statistics_categorical(const std::vector<Questions*>& all_questions) {
    std::map<std::string, std::vector<int>> report;
    std::map<std::string, std::vector<Questions*>> maped_all_questions = Questions::categoricalize_question_and_sort(all_questions);
    for (auto& [key, questions] : maped_all_questions) {
        std::vector<int> statistic = report_statistics(questions);
        report.insert({key, statistic});
    }
    report.insert({"total", report_statistics(all_questions)});
    return report;
}

std::vector<int> Report::report_statistics(const std::vector<Questions*> questions) {
    int total_correct = 0, total_incorrect = 0, total_blank = 0;
    for (auto& question : questions) {
        total_correct += question->get_statistic_question()[0];
        total_incorrect += question->get_statistic_question()[1];
        total_blank += question->get_statistic_question()[2];
    }
    return {total_correct, total_incorrect, total_blank};
}

double Report::calculate_score(const std::vector<int>& statistics) {
    if (statistics[0] + statistics[1] + statistics[2] != 0)
        return (double)statistics[0] / (statistics[0] + statistics[1] + statistics[2]);
    else
        return 0.0;
}