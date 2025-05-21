#ifndef CSV_HPP
#define CSV_HPP

#include <string>

class Csv {
private:
    std::string path;

public:
    Csv(std::string path);
    void parsing_csv();
    static void parse_line_csv(std::string line);
};

#endif 