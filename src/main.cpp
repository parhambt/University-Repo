#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

class CSV
{
private:
    vector<map<pair<string, string>, vector<pair<string, string>>>> csv_rows;
    string path;

public:
    CSV(string path) { this->path = path; }
    void parsing_csv()
    {
        ifstream csv(this->path);
        string line;
        while (getline(csv, line))
        {
            auto row_data = parse_line(line);
            this->csv_rows.push_back(row_data);
        }
    }
    static map<pair<string, string>, vector<pair<string, string>>> parse_line(string line)
    {
        istringstream current_line(line);
        string question_text;
        string option1;
        string option2;
        string option3;
        string option4;
        string correct_answer;
        string difficulty;
        string subject;
        getline(current_line, question_text, ',');
        getline(current_line, option1, ',');
        getline(current_line, option2, ',');
        getline(current_line, option3, ',');
        getline(current_line, option4, ',');
        getline(current_line, correct_answer, ',');
        getline(current_line, difficulty, ',');
        getline(current_line, subject);
        map<pair<string, string>, vector<pair<string, string>>> parsed_line = {
            {
                make_pair(subject, difficulty),
                {
                    make_pair("Question", question_text),
                    make_pair("opt1", option1),
                    make_pair("opt2", option2),
                    make_pair("opt3", option3),
                    make_pair("opt4", option4),
                    make_pair("correct ans" , correct_answer) , 
                }
            }
        };
        return parsed_line ; 
}} ; 

int main()
{
    CSV a("questions.csv") ; 
    a.parsing_csv();
}

