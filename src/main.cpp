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
const string NUM_INCORRECTS = "numOfIncorrects" ; 
const string NUM_BLANKS = "numOfBlanks" ; 
const string NUM_CORRECTS = "numOfCorrects" ; 
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
    vector<map<vector<string>, vector<map<string, string>>>> csv_questions;
    string path;

public:
    CSV(string path) { this->path = path; }
    void parsing_csv()
    {
        ifstream csv(this->path);
        string line;
        while (getline(csv, line))
        {
            auto row_data = CSV::parse_line_csv(line);
            this->csv_questions.push_back(row_data);
        }
    }
    vector<map<vector<string>, vector<map<string, string>>>> getCsv()
    {
        return this->csv_questions ; 
    }
    static map<vector<string>, vector<map<string, string>>> parse_line_csv(string line)
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
        vector<string> question_info = {question_text, difficulty, subject};

        vector<map<string, string>> answer_info = {
            { {"OPT1", option1} },
            { {"OPT2",option2} },
            { {"OPT3", option3} },
            { {"OPT4", option4} },
            { {"CORRECT_ANS", correct_answer} },
            { {"NUM_BLANKS", "0"} },
            { {"NUM_CORRECTS", "0"} },
            { {"NUM_INCORRECTS", "0"} }
        };
    
        map<vector<string>, vector<map<string, string>>> parsed_line = {
            { question_info, answer_info }
        };
        return parsed_line ; 
}} ; 


class QUESTIONS
{
private : 
    int num_blanks , num_corrects , num_incorrect  ;

public : 
    string question_text,difficulty,subject,option1,option2,option3,option4,correct_answer; 
     
    QUESTIONS(string question_text , string difficulty , string subject , string option1 , string option2 , string optio3 , string option4,string correct_answer)
    {
        this->question_text = question_text ; 
        this->difficulty = difficulty ; 
        this->subject =subject ; 
        this->option1 = option1 ; 
        this->option2 = option2 ;
        this->option3 = option3 ;
        this->option4 = option4 ;
        this->correct_answer = correct_answer ; 
        this->num_blanks = 0 ; 
        this->num_corrects = 0 ; 
        this->num_incorrect = 0  ; 

    }
    void set_num_blanks(int blanks)
    {
        this->num_blanks = blanks ; 
    }
    void set_num_incorrects(int incorrects)
    {
        this->num_incorrect = incorrects ; 
    }
    void set_num_corrects(int corrects)
    {
        this->correct_answer = corrects ; 
    }
    
   
};


int main(int argc , char * argv[])
{
    CSV csv_question("questions.csv") ; 
    csv_question.parsing_csv();
    IO::input_handelling() ; 

}

