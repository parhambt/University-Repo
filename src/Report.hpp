#ifndef REPORT_HPP
#define REPORT_HPP

#include <vector>
#include <map>
#include "Questions.hpp"

class Report {
public:
    static std::map<std::string, std::vector<int>> report_statistics_categorical(const std::vector<Questions*>& all_questions);
    static std::vector<int> report_statistics(const std::vector<Questions*> questions);
    static double calculate_score(const std::vector<int>& statistics);
};

#endif 