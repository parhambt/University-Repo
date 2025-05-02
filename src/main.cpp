#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;


const string CREATE_TEMP = "create_template" ; 
const string GENERATE_TEST = "generate_test" ; 
const string ATTEND = "attend" ; 
const string AUTO_GENERATE = "auto_generate" ; 
const string REPORT = "report" ; 
const string ALL = "all" ; 
const string TEST = "test" ; 
const string TESTS = "tests" ; 
const string SUBJECT = "subject" ; 
const string QUESTION = "Question" ; 
const string OPT1 = "opt1" ; 
const string OPT2 = "opt2" ;
const string OPT3 = "opt3" ; 
const string OPT4 = "opt4" ; 
const string CORRECT_ANS = "correct ans" ; 
class CSV ; 

class EXAM
{
private : 
    CSV * data_csv ; 
    inline static vector<map<string , vector<vector<string>>>> templates_exam={} ; 
public : 
    EXAM(CSV * data_csv)
    {
        this->data_csv = data_csv ; 
    }
    static void add_template(const map<string , vector<vector<string>>> & template_exam)
    {
        EXAM::templates_exam.push_back(template_exam) ; 
    }
};


class IO
{
public : 
     
    static void input_handelling()
    {
        string line ; 
        while(getline(cin,line))
        {
            istringstream current_line(line) ;
            string input ;
            current_line >> input ; 
            if(input==CREATE_TEMP)
            {
                EXAM::add_template(parse_template_data(current_line)) ; 
            }
        }
    }
    static map<string , vector<vector<string>>> parse_template_data(istringstream & given_data)
    {
        string single_data ,template_name; 
        char single_quote ; 
        vector<vector<string>> parsed_data ; 
        given_data>>ws>>single_quote ; 
        getline(given_data , template_name , '\'') ; 
        given_data>>ws ; 
        while(getline(given_data,single_data,' '))
        {
            istringstream exam_detail(single_data) ; 
            string subj , difficulty , count ;
            getline(exam_detail,subj,':') ; 
            getline(exam_detail,difficulty,':') ; 
            getline(exam_detail,count,' ') ; 
            parsed_data.push_back({subj,difficulty,count}) ; 
        }
        return {{template_name,parsed_data}}  ;
    }
};




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
    vector<map<pair<string, string>, vector<pair<string, string>>>> getCsv()
    {
        return this->csv_rows ; 
    }
    static map<pair<string, string>, vector<pair<string, string>>> parse_line(string line)
    {
        istringstream current_line(line);
        string question_text , option1,option2,option3,option4,correct_answer,difficulty,subject;
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
                    make_pair(QUESTION, question_text),
                    make_pair(OPT1, option1),
                    make_pair(OPT2, option2),
                    make_pair(OPT3, option3),
                    make_pair(OPT4, option4),
                    make_pair(CORRECT_ANS , correct_answer) , 
                }
            }
        };
        return parsed_line ; 
}} ; 


int main(int argc , char * argv[])
{
    CSV csv_question("questions.csv") ; 
    csv_question.parsing_csv();
    IO::input_handelling() ; 

}

