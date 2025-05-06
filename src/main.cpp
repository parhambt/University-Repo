#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include<algorithm>
#include <iomanip>
#include <string>
#include <set>
#include <cctype>
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
const string QUESTION_TEXT = "question_text" ; 
const string OPTION1 = "option1" ; 
const string OPTION2 = "option2" ;
const string OPTION3 = "option3" ; 
const string OPTION4 = "option4" ; 
const string CORRECT_ANS = "correct ans" ; 
const string NUM_INCORRECTS = "numOfIncorrects" ; 
const string NUM_BLANKS = "numOfBlanks" ; 
const string NUM_CORRECTS = "numOfCorrects" ; 
const string EASY = "easy" ; 
const string MEDIUM = "medium" ;
const string HARD = "hard" ; 
const vector<string> DIFFICULTY =  {EASY, MEDIUM ,HARD} ; 

const string  TAB = "    " ; 
const string FLASH = " <-" ; 
const vector<vector<string>> NONE_VECTOR = {{"NONE","NONE"}} ; 


class Questions;

class Exam
{
private : 
    vector<Questions*> exam_questions ; 
    string exam_name ; 
    int num_corrects , num_incorrects , num_blanks ; 
    inline static map<string , vector<vector<string>>> templates_exam={} ; 
    inline static map<string , Exam *> all_exams={} ; 
    inline static vector<Exam*> all_exams_attend = {} ; 
public : 
    Exam(vector<Questions*> exam_questions,string exam_name)
    {
        this->exam_questions = exam_questions ; 
        this->exam_name = exam_name ; 
        all_exams.insert({exam_name,this}) ; 
    }
    void set_statistics_exam(int num_corrects , int num_incorrects , int num_blanks)
    {
        this->num_corrects = num_corrects ; 
        this-> num_incorrects = num_incorrects ; 
        this->num_blanks = num_blanks ; 
    }
    vector<int> get_statistics_exam()
    {
        return {this->num_corrects , this->num_incorrects , num_blanks} ; 
    }
    static void add_template(const map<string , vector<vector<string>>> & template_exam)
    {
        Exam::templates_exam.insert(*template_exam.begin()) ; 
    }
    static  vector<vector<string>> get_template_exam(string template_name)
    {
        if(Exam::templates_exam.find(template_name)!=Exam::templates_exam.end())
            return Exam::templates_exam[template_name] ; 
        else return NONE_VECTOR ; 
    }
    static Exam * get_exam(string exam_name)
    {
        auto exam = Exam::all_exams.find(exam_name) ; 
        if(exam==Exam::all_exams.end()) return nullptr ; 
        return  exam->second ; 
    }
    vector<Questions*> get_exams_questions()
    {
        return this->exam_questions ; 
    }
    static void add_exam_attends(Exam * exam )
    {
        Exam :: all_exams_attend.push_back(exam) ; 
    }
    static vector<Exam*> get_exams_attends()
    {
        return Exam::all_exams_attend ;
    }
    string get_exam_name()
    {
        return this->exam_name ; 
    }
    static vector<Questions*> map_to_vector(const map<string ,vector<Questions*>> &all_questions)
    {
        vector<Questions*> vector ; 
        for(const auto& [key,questions]:all_questions)
        {
            for(const auto& question:questions)
            {
                vector.push_back(question) ; 
            }
        }
        return vector ; 
    }


};



class Questions
{
private : 
    int num_blanks , num_corrects , num_incorrect , priority,choosen_option ,num_seen_question ;
    string question_text,difficulty,subject,option1,option2,option3,option4,correct_answer;
    inline static map<pair<string,string> , vector<Questions * >> all_questions={} ; 
    inline static vector<Questions * > all_questions_vector={} ; 
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
        this->choosen_option = -1 ; 
        this->num_seen_question = 0 ; 
        Questions::all_questions[make_pair(subject,difficulty)].push_back(this) ; 
        Questions::all_questions_vector.push_back(this) ; 

    }
    static vector<Questions *> get_questions_by_subject(string subject)
    {
        vector<Questions *> all_questions  ; 
        for(auto difficulty:DIFFICULTY)
        {
            auto questions = Questions::all_questions[make_pair(subject , difficulty)] ; 
            all_questions.insert(all_questions.end(),questions.begin() , questions.end()) ; 
        }
        return all_questions ; 
    }
    static vector<string> find_all_subject()
    {
        set<string> all_subject ; 
        auto all_questions = Questions::all_questions ; 
        for(auto& [key,value]:all_questions)
        {
            all_subject.insert(key.first) ; 
        }
        return vector(all_subject.begin(),all_subject.end()) ; 
    }
    static vector<Questions*> choose_question_from_two_least_subject_avg()
    {
        vector<Questions*> choosen_questions ;  
        choosen_questions.reserve(10) ; 
        auto subject_ratio_correctness = Questions :: subject_ratio_correct_answer() ; 
        auto sort_ratio = [](pair<string , double> &a , pair<string,double>&b)
        {
            if(a.second!=b.second)
            {
                if(a.second < b.second) return true ; 
                else return false ; 
            }
            if(a.first < b.first) return true ; 
            else return false ; 
        } ; 
        sort(subject_ratio_correctness.begin(),subject_ratio_correctness.end() , sort_ratio) ; 
        string subject1 = subject_ratio_correctness[0].first , subject2 = subject_ratio_correctness[1].first ;
        vector<vector<string>> template_exam={{subject1,EASY,"3"},{subject1,MEDIUM,"2"},{subject1,HARD,"1"},{subject2,EASY,"2"},{subject2,MEDIUM,"1"},{subject2,HARD ,"1"}} ;
        choosen_questions = Questions:: choose_question_by_priority(template_exam) ; 
        
        return choosen_questions ; 
    }
    static vector<pair<string , double>> subject_ratio_correct_answer()
    {
        vector<pair<string , double>> answer ; 
        vector<string> all_subject = Questions::find_all_subject() ;
        for(auto subject: all_subject)
        {
            int count_true = 0  , all_seen_questions=0; 
            auto all_question_subject = get_questions_by_subject(subject) ; 
            for(auto& question:all_question_subject)
            {
                if(question->choosen_option == stoi(question->correct_answer)) count_true++ ; 
                all_seen_questions+= question->num_seen_question ; 

            }
            if(all_seen_questions==0) answer.push_back(make_pair(subject , 0)) ; 
            else  answer.push_back({subject , (double)count_true / all_seen_questions}) ; 
        }
        return answer ; 

    }
    static map<pair<string,string> , vector<Questions * >>& get_all_questions()
    {
        return Questions::all_questions ; 
    }
    static vector<Questions*> get_all_questions_vector()
    {
        return Questions::all_questions_vector ; 
    }
    vector<int> get_statistic_question()
    {
        return {this->num_corrects , this->num_incorrect , this->num_blanks} ; 
    }
    int get_choosen_option()
    {
        return this->choosen_option ; 
    }
    string get_question_detail(string specific_part_question)
    {
        if(specific_part_question=="question_text") return this->question_text ; 
        else if (specific_part_question=="option1") return this->option1 ; 
        else if ( specific_part_question=="option2") return this->option2 ; 
        else if (specific_part_question=="option3") return this->option3 ; 
        else if (specific_part_question=="option4") return this->option4 ;
        else return "NONE" ; 
    }
    bool evaluate_answer(string choosen_answer)
    {
        if(this->correct_answer == choosen_answer) return true ; 
        else return false ; 
    }
    static bool look_like_proper_answer(string choosen_answer)
    {
        if(choosen_answer=="1"||choosen_answer=="2"||choosen_answer=="3"||choosen_answer=="4"||choosen_answer.empty()) return true  ; 
        else return false ; 
    }
    void choose_answer_for_now(string choosen_answer)
    {
        if(choosen_answer=="1"||choosen_answer=="2"||choosen_answer=="3"||choosen_answer=="4")
        {
            this->choosen_option = stoi(choosen_answer) ;    
        }
        else if(choosen_answer.empty()) 
        {
            this->choosen_option = 0 ; 
        }
        
        
    }
    static void choose_answer(const pair<Exam *,map<Questions* , string>> &questions_with_answer)
    {
        auto exam = questions_with_answer.first ;
        int num_corrects=0 , num_incorrect=0 , num_blanks=0 ; 
        for(const auto& [question,answer]:questions_with_answer.second)
        {
            if(answer.empty()) question->choosen_option = 0 ; 
            else question->choosen_option = stoi(answer) ;
            if(answer == question->correct_answer)
            {
                question->num_corrects +=1 ; 
                num_corrects++;
            }
            else if ( answer.empty()) 
            {
                question->num_blanks +=1 ;
                num_blanks++ ; 
            } 
            else 
            {
                question->num_incorrect +=1 ; 
                num_incorrect++ ;
            }
            question->priority_calculator() ; 
            question->num_seen_question +=1 ;
        }
        exam->set_statistics_exam(num_corrects , num_incorrect , num_blanks) ; 
        
    }
    void priority_calculator()
    {
        int priority = 3*(this->num_incorrect)   + this->num_blanks - 2*(this->num_corrects)  ;
        this->priority = priority ; 
    }
    static bool sort_priority(Questions * a , Questions * b)
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
    }
    static vector<Questions * > choose_question_by_priority(const vector<vector<string>>& template_exam)
    {
        vector<Questions * > choosen_questions ; 
        for(auto single_info_temp : template_exam)
        {
            string subject=single_info_temp[0] , difficulty=single_info_temp[1] ; 
            int count = stoi(single_info_temp[2]) ; 
            vector<Questions * > & all_questions = Questions::get_all_questions()[make_pair(subject , difficulty)] ; 

            sort(all_questions.begin(),all_questions.end(),Questions::sort_priority) ; 
            vector<Questions * > choosen_question (all_questions.begin(),all_questions.begin()+count) ;
            choosen_questions.insert(choosen_questions.end(),choosen_question.begin(),choosen_question.end()) ; 
        } 
        return choosen_questions ; 
    }
    static map<string , vector<Questions *>> categoricalize_question_and_sort(const vector<Questions*>&exam_questions)
    {

        map<string , vector<Questions *>> categoricaled_question ; 
        for(auto question:exam_questions)
        {
            string subject = question->subject ; 
            categoricaled_question[subject].push_back(question) ; 
        }

        for(auto& [key,value]:categoricaled_question)
        {
            sort(value.begin(),value.end(),[](Questions * a , Questions * b )
            {
            if(a->question_text < b->question_text) return true ; 
            else return false ; 
            });
        }
        return categoricaled_question ; 
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
        getline(csv,line) ; 
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
        new Questions (question_text , difficulty , subject , option1 , option2 , option3 , option4 , correct_answer)  ;         
    }
} ; 
class Report
{
private : 

public : 
    static map<string,vector<int>> report_statistics_categorical(const vector<Questions *> &all_questions) 
    {
        map<string,vector<int>> report ; 
        map<string , vector<Questions *>> maped_all_questions=Questions::categoricalize_question_and_sort(all_questions) ;
        for(auto& [key,questions ]: maped_all_questions)
        {
            vector<int> statistic = report_statistics(questions) ; 
            report.insert({key,statistic}) ;
        }
        report.insert({"total",report_statistics(all_questions)}) ; 
        return report ; 
    }
    static vector<int> report_statistics(const vector<Questions*> questions)
    {
        int total_correct =0, total_incorrect=0 , total_blank=0 ; 
        for(auto& question:questions)
        {
            total_correct+= question->get_statistic_question()[0] ; 
            total_incorrect += question->get_statistic_question()[1] ; 
            total_blank += question->get_statistic_question()[2] ; 
        }
        return {total_correct , total_incorrect , total_blank } ; 
    }

    static double calculate_score(const vector<int> &statistics)
    {
        return statistics[0]/(statistics[0]+statistics[1]+statistics[2]) ;
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
                if(Exam::get_template_exam(template_name)==NONE_VECTOR)
                {
                    Exam::add_template({{template_name,parse_template_data(current_line)}}) ; 
                    cout<<"Template \'"<<template_name<<"\' was created successfully.\n" ; 
                }
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
                    new Exam (exam_questions , exam_name) ; 
                    cout<<"Test \'"<<exam_name<<"\' was generated successfully.\n" ;
                }

            }
            else if (input==ATTEND)
            {
                string test_name = parse_word_in_quote(current_line) ; 
                Exam * exam= Exam::get_exam(test_name) ; 
                if (exam==nullptr) cout<<"Could not find test: \'"<<test_name<<"\'\n";
                else
                {
                    Exam::add_exam_attends(exam) ; 
                    vector<Questions*> exam_questions=exam->get_exams_questions();
                    auto categoricaled_question = Questions::categoricalize_question_and_sort(exam_questions) ; 
                    IO::print_exam(categoricaled_question , test_name , exam ) ;
                }
            }
            else if(input==AUTO_GENERATE)
            {
                string test_name=IO::parse_word_in_quote(current_line) ;
                auto exam_questions = Questions::choose_question_from_two_least_subject_avg() ; 
                new Exam (exam_questions , test_name)  ; 
                cout<<"Test \'"<<test_name<<"\' was generated successfully.\n" ; 
            }
            else if(input == REPORT)
            {
                string next_input  ; 
                current_line>>next_input ; 
                if(next_input==ALL)
                {
                    IO::print_report(0 , ALL) ;
                }
                else if (next_input==TEST)
                {
                    string test_name=IO::parse_word_in_quote(current_line) ;
                    IO::print_report(1,test_name) ; 
                }
                else if (next_input==TESTS)
                {
                    IO::report_tests() ; 
                }
                else if(next_input==SUBJECT)
                {
                    string subject_name = IO::parse_word_in_quote(current_line) ; 
                    IO::report_subject(subject_name) ;
                }
            }
            
        }
    }
    static void report_subject(string subject)
    {
        cout<<"Results for "<<subject<<":\n" ; 
        vector<Questions*> all_questions ; 
        for(auto difficulty : DIFFICULTY)
        {
            auto questions = Questions::get_all_questions()[make_pair(subject , difficulty)] ;
            all_questions.reserve(questions.size()) ; 
            all_questions.insert(all_questions.end() , questions.begin(),questions.end()) ; 
            auto statistics = Report::report_statistics(questions);
            print_static(statistics , difficulty , false) ; 
        }
        auto all_staticstic = Report::report_statistics(all_questions); 
        string total_score =  three_figure(Report::calculate_score(all_staticstic)) ;
        cout<<"Total score: "<<total_score<<".\n" ; 
    }
    static void print_report(int stage , string test_name)
    {
        if(stage==0) cout<<"Total report:\n" ;
        else cout<<"Results for "<<test_name<<":\n" ; 
        map<string,vector<int>> statistics ; 
        if(stage ==0) statistics = Report::report_statistics_categorical(Questions::get_all_questions_vector()) ; 
        else 
        {
            auto exam =Exam::get_exam(test_name) ; 
            auto exam_questions = exam->get_exams_questions() ; 
            statistics = Report::report_statistics_categorical(exam_questions);
        }
        for(auto [key,statistic]:statistics)
        {
            if(key=="total") continue;
            // string score = three_figure(Report::calculate_score(statistic)) ; 
            // cout<<key<<": "<<statistic[0]<<" corrects, "<<statistic[1]<<" incorrects and "<<statistic[2]<<" blanks. Score: "<<score<<"%.\n" ; 
            IO::print_static(statistic , key,true)  ;
        }
        cout<<"\nTotal results: "<<statistics["total"][0]<<" corrects, "<<statistics["total"][1]<<" incorrects and "<<statistics["total"][2]<<"blanks.\n" ; 
        string total_score =  three_figure(Report::calculate_score(statistics["total"])) ;
        cout<<"Total score: "<<total_score<<".\n" ; 

    }
    static void print_static(const vector<int>&statistic , string key , bool is_score)
    {
        if(is_score) 
        {    
            string score = three_figure(Report::calculate_score(statistic)) ;
            cout<<key<<": "<<statistic[0]<<" corrects, "<<statistic[1]<<" incorrects and "<<statistic[2]<<" blanks. Score: "<<score<<".\n" ;
        }
        else
        {
            cout<<key<<": "<<statistic[0]<<" corrects, "<<statistic[1]<<" incorrects and "<<statistic[2]<<" blanks.\n" ;
        }
    }
    static void report_tests()
    {
        cout<<"Results per attended tests:\n" ; 
        auto exams = Exam::get_exams_attends() ; 
        for(auto& exam : exams)
        {
            string exam_name =exam->get_exam_name() ; 
            auto exam_questions = exam->get_exams_questions() ; 
            auto statistics = Report::report_statistics(exam_questions) ; 
            // string score = three_figure(Report::calculate_score(statistics)) ; 
            // cout<<exam_name<<": "<<statistics[0]<<" corrects, "<<statistics[1]<<" incorrects and "<<statistics[2]<<"blanks. Score: "<<score<<"%.\n" ; 
            IO::print_static(statistics , exam_name,true) ; 

        }
    }
    
    static string three_figure(double value) {
        ostringstream out;
        out << fixed << setprecision(3) << (value * 100) << "%";
        return out.str();
    }
    static void print_exam(const map<string , vector<Questions *>>& categoricaled_question,string test_name , Exam * exam)
    {
        pair<Exam *,map<Questions* , string>> questions_with_answer ; 
        questions_with_answer.first = exam ; 
        cout<<test_name <<":\n" ;
        int count = 1 , count_prev=0; 
        vector<Questions*> questions_vector = Exam::map_to_vector(categoricaled_question) ; 
        auto it  = questions_vector.begin() ; 
         
        while( it!=questions_vector.end() )
        {
            
            bool is_valid_option = false ; 
            
            
            int choosen_answer = (*(it))->get_choosen_option() ; 
            if(is_valid_option==false)
            {
                IO::option_printer(choosen_answer,it,count,count_prev) ; 
            }
            bool state=IO::enter_option(it,is_valid_option,questions_vector , questions_with_answer ) ;
            if(state==false) 
            {
                --it ; --count ;
                ++count_prev ;  
            }
            else 
            {
                ++it ; ++count ;
                if(count_prev<= 0 ) count_prev = 0 ;
                else --count_prev ;  
            }  
                
            
            
        } 
        Questions::choose_answer(questions_with_answer) ; 
        cout<<"Finished "<<test_name<<".\n" ; 
    }

    

    
    
    
    static void option_printer(int choosen_answer,const vector<Questions*>::iterator it,int count , int count_prev )
    {
        

        cout<<count<<") "<<(*it)->get_question_detail(QUESTION_TEXT)<<endl; 

        if(choosen_answer==1 && count_prev>0) cout<<TAB<<"1. "<<(*it)->get_question_detail(OPTION1)<<FLASH<<endl; 
        else   cout<<TAB<<"1. "<<(*it)->get_question_detail(OPTION1)<<endl; 

        if(choosen_answer==2 && count_prev>0)cout<<TAB<<"2. "<<(*it)->get_question_detail(OPTION2)<<FLASH<<endl ;
        else   cout<<TAB<<"2. "<<(*it)->get_question_detail(OPTION2)<<endl ;
        
        if(choosen_answer==3 && count_prev>0)cout<<TAB<<"3. "<<(*it)->get_question_detail(OPTION3)<<FLASH<<endl ;
        else   cout<<TAB<<"3. "<<(*it)->get_question_detail(OPTION3)<<endl;
        
        if(choosen_answer==4 && count_prev>0)cout<<TAB<<"4. "<<(*it)->get_question_detail(OPTION4)<<FLASH<<endl;
        else  cout<<TAB<<"4. "<<(*it)->get_question_detail(OPTION4)<<endl  ;
    }
    static bool enter_option( vector<Questions*>::iterator &it, bool &is_valid_option,vector<Questions*> &questions , pair<Exam *,map<Questions* , string>> & questions_with_answer )
    {
        while(is_valid_option!=true)
        {
            string answer ; 
            cout<<"Your answer: " ; 
            getline(cin,answer) ;
            // is_valid_option =(*it)->choose_answer(answer) ; 
            is_valid_option = Questions::look_like_proper_answer(answer) ; 
            (*it)->choose_answer_for_now(answer) ;
            if(is_valid_option) questions_with_answer.second.insert_or_assign((*it) ,answer ) ; 
            if(answer =="previous" && questions.begin()!=it) return false ; 
            else if(answer == "previous" && questions.begin() == it) is_valid_option = false ; 
            if(is_valid_option==false) cout<<"Invalid answer, please try again.\n" ; 
        }
        return true ; 
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




int main(int argc , char * argv[])
{
    Csv csv_question("questions.csv") ; 
    csv_question.parsing_csv();
    IO::input_handelling() ; 

}

