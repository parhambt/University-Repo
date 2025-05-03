#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include<algorithm>
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
const vector<vector<string>> NONE_VECTOR = {{"NONE","NONE"}} ; 

class CSV ; 
class IO ; 
class Questions ; 
class Exam ; 


class Exam
{
private : 
    vector<Questions*> exam_questions ; 
    string exam_name ; 
    inline static map<string , vector<vector<string>>> templates_exam={} ; 
    inline static map<string , Exam *> all_exams={} ; 
public : 
    Exam(vector<Questions*> exam_questions,string exam_name)
    {
        this->exam_questions = exam_questions ; 
        this->exam_name = exam_name ; 
        all_exams.insert({exam_name,this}) ; 
    }
    static void add_template(const map<string , vector<vector<string>>> & template_exam)
    {
        Exam::templates_exam.insert(template_exam.begin(),template_exam.end()) ; 
    }
    static  vector<vector<string>> get_template_exam(string template_name)
    {
        if(Exam::templates_exam.find(template_name)!=Exam::templates_exam.end())
            return Exam::templates_exam[template_name] ; 
        else return NONE_VECTOR ; 
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
                string template_name = IO::parse_word_in_quote(current_line) ; 
                if(Exam::get_template_exam(template_name)!=NONE_VECTOR)
                    Exam::add_template({{template_name,parse_template_data(current_line)}}) ; 
                else 
                {
                    cout<<"Duplicate name: \'"<<template_name<<"\'" <<endl; 
                }
            }
            else if (input==GENERATE_TEST)
            {
                string exam_name , template_name ; 
                exam_name=IO::parse_word_in_quote(current_line) ; 
                template_name=IO::parse_word_in_quote(current_line) ;
                auto template_exam=Exam::get_template_exam(template_name) ; 
                if(template_exam==NONE_VECTOR) cout<<"Could not find template: \'"<<template_name<<"\'"<<endl ; 
                else
                {
                    vector<Questions * > exam_questions = Questions::choose_question_by_priority(template_exam) ; 
                    Exam exam(exam_questions , exam_name) ; 
                }

            }
            
        }
    }
    static  vector<vector<string>> parse_template_data(istringstream & given_line)
    {
        string single_data; 
        vector<vector<string>> parsed_data ; 
        while(getline(given_line,single_data,' '))
        {
            istringstream exam_detail(single_data) ; 
            string subj , difficulty , count ;
            getline(exam_detail,subj,':') ; 
            getline(exam_detail,difficulty,':') ; 
            getline(exam_detail,count,' ') ;  
            parsed_data.push_back({subj,difficulty,count}) ; 
        }
        return parsed_data ;
    }
    static string parse_word_in_quote(istringstream & given_line)
    {
        string target_word  ; 
        char single_quote ;
        given_line>>ws>>single_quote ; 
        getline(given_line , target_word , '\'') ;
        given_line>>ws ; 
        return target_word ; 
    }
};

class Questions
{
private : 
    int num_blanks , num_corrects , num_incorrect , priority  ;
    string question_text,difficulty,subject,option1,option2,option3,option4,correct_answer;
    inline static map<pair<string,string> , vector<Questions * >> all_questions={} ; 
public : 
     
     
    Questions(string question_text , string difficulty , string subject , string option1 , string option2 , string option3 , string option4,string correct_answer)
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
        Questions::all_questions[make_pair(subject,difficulty)].push_back(this) ; 

    }
    static map<pair<string,string> , vector<Questions * >>& get_all_questions()
    {
        return Questions::all_questions ; 
    }
    void set_num_blanks(int blanks)
    {
        this->num_blanks = blanks ; 
        priority_calculator() ; 

    }
    void set_num_incorrects(int incorrects)
    {
        this->num_incorrect = incorrects ; 
        priority_calculator() ; 
    }
    void set_num_corrects(int corrects)
    {
        this->num_corrects = corrects ;
        priority_calculator() ; 
    }
    void priority_calculator()
    {
        int priority = 3*(this->num_incorrect)   + this->num_blanks - 2*(this->num_corrects)  ;
        this->priority = priority ; 
    }
    static vector<Questions * > choose_question_by_priority(const vector<vector<string>>& template_exam)
    {
        vector<Questions * > choosen_questions ; 
        for(auto single_info_temp : template_exam)
        {
            string subject=single_info_temp[0] , difficulty=single_info_temp[1] ; 
            int count = stoi(single_info_temp[2]) ; 
            vector<Questions * > & all_questions = Questions::get_all_questions()[make_pair(subject , difficulty)] ; 
            auto sort_priority = [](Questions * a , Questions * b)
            {
                if((a->priority!=b->priority ))
                {
                    if(a->priority > b->priority) return true ;
                    else return false ; 
                }
                else
                {
                    if(a->question_text < b->question_text) return true ; 
                    else return false ; 
                }
            } ; 
            sort(all_questions.begin(),all_questions.end(),sort_priority) ; 
            vector<Questions * > choosen_question (all_questions.begin(),all_questions.begin()+count) ;
            choosen_questions.insert(choosen_questions.end(),choosen_question.begin(),choosen_question.end()) ; 
        } 
        return choosen_questions ; 
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





int main(int argc , char * argv[])
{
    Csv csv_question("questions.csv") ; 
    csv_question.parsing_csv();
    IO::input_handelling() ; 

}

