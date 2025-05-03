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

class Exam
{
private : 
    CSV * data_csv ; 
    inline static vector<map<string , vector<vector<string>>>> templates_exam={} ; 
public : 
    Exam(CSV * data_csv)
    {
        this->data_csv = data_csv ; 
    }
    static void add_template(const map<string , vector<vector<string>>> & template_exam)
    {
        Exam::templates_exam.push_back(template_exam) ; 
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
                Exam::add_template(parse_template_data(current_line)) ; 
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



class Csv
{
private:
    string path;
public:
    Csv(string path) { this->path = path; }
    void parsing_csv()
    {
        ifstream csv(this->path);
        string line;
        while (getline(csv, line))
        {
            Csv::parse_line_csv(line) ; 
        }
    }
    static void parse_line_csv(string line)
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
        Questions q(question_text , difficulty , subject , option1 , option2 , option3 , option4 , correct_answer)  ;         
    }
} ; 


class Questions
{
private : 
    int num_blanks , num_corrects , num_incorrect , priority  ;
    string question_text,difficulty,subject,option1,option2,option3,option4,correct_answer;
    static vector<Questions *> all_questions ; 
public : 
     
     
    Questions(string question_text , string difficulty , string subject , string option1 , string option2 , string optio3 , string option4,string correct_answer)
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
        this->priority = 0 ; 
        all_questions.push_back(this) ;

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
    static vector<Questions * > select_question_by_priority()
    {

    }

   
};


int main(int argc , char * argv[])
{
    Csv csv_question("questions.csv") ; 
    csv_question.parsing_csv();
    IO::input_handelling() ; 

}

