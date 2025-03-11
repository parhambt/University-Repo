#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h> 
using namespace std ; 

const string WINDOW = "window" ; 
const string DOOR = "door" ; 
const string MIDDLE = "middle" ; 
const string SHOW_TABLE_INFO = "show_table_info" ; 
const string ENTER = "enter" ; 
const string RESERVER_TABLE = "reserve_table" ; 
const string EXIT = "exit" ; 
const string SWITCH = "switch" ; 

typedef struct Table Table ; 
typedef struct Students Students ; 

void read_table(char * filepath,map<int,Table> &tables) ; 
void read_student(char * filepath , map<int,Students> &students_map) ; 
int find_student_table(int student_id , const map<int,Table> &tables_map) ; 
map<int,int> calaulate_tables_score(int student_id, const map<int,Table> &tables , const map<int,Students> &students) ; 
int calculate_one_table_score(const map<int,Table> &tables ,int current_table_id ,int friend_table_id , int enemy_table_id ) ; 
list<string> sort_students_name(const map<int,Students> &students) ; 
void show_table_info (int table_id,const map<int,Table> &tables) ;
bool compare(pair<int,int> &a , pair<int,int>&b) ; 
void enter(int student_id, const map<int,Table> &tables , const map<int,Students> &students) ;
vector<pair<int,int>> map_to_sorted_vector(const map<int,int>&a ) ;
void reserve_table(const vector<int> &inputs,map<int,Table> &tables , const map<int,Students> &students,int flag) ;
void exit(int student_id,map<int,Table> &tables , map<int,Students>&students) ; 
void _switch(int student_id,map<int,Table> &tables , map<int,Students>&students) ; 
void input_handeling(map<int,Table> &tables , map<int,Students>&students) ;

typedef struct Table
{
    // int ID ; 
    int X ; 
    int Y ; 
    int capacity ; 
    string type ; 
    map<int,Students> students ; 
    map<int ,Students> queue_student ; 

}Table ; 

typedef struct Students
{
    // int ID ; 
    string name ; 
    int friend_id ;
    int enemy_id ;  
}Students ; 


int main(int argc , char * argv[])
{
    map<int,Table> tables; 
    map<int,Students> students ; 
    read_table(argv[1],tables) ; 
    read_student(argv[2],students) ; 
    input_handeling(tables,students) ; 

}
void input_handeling(map<int,Table> &tables , map<int,Students>&students)
{
    string line ; 
    while(getline(cin,line))
    {
        std::regex del(" ")  ;
        sregex_token_iterator it(line.begin(),line.end(),del,-1) ; 
        sregex_token_iterator end ;
        if(*it==SHOW_TABLE_INFO)
        {
            
            int arg1= stoi(*(++it))  ; 
            show_table_info(arg1 ,tables) ; 

        }
        else if(*it==ENTER)
        {
            int arg1= stoi(*(++it))  ; 
            enter(arg1,tables,students) ; 
        }
        else if(*it==RESERVER_TABLE)
        {
            int arg1= stoi(*(++it))  ; 
            
            vector<int> inputs ={arg1} ; 
            if(it!=end) 
            {
                
                int arg2 = stoi(*(++it)) ; 
                
                inputs ={arg1,arg2} ;
            }
            
            reserve_table(inputs ,tables,students,0) ; 
        }
        else if (*it==EXIT)
        {
            int arg1= stoi(*(++it))  ; 
            exit(arg1,tables,students) ; 
        }
        else if(*it==SWITCH)
        {
            int arg1= stoi(*(++it))  ; 
            _switch(arg1,tables,students);
        }
    }
}


void _switch(int student_id,map<int,Table> &tables , map<int,Students>&students)
{
    int student_table_id = find_student_table(student_id ,tables) ; 
    int friend_id = students.find(student_id)->second.friend_id ; 
    int friend_table_id = find_student_table(friend_id , tables) ; 
    Students student = students.find(student_id)->second ; 
    Students friend_student = students.find(friend_id)->second ; 
    tables.find(student_table_id)->second.students.erase(student_id) ; 
    tables.find(friend_table_id)->second.students.erase(friend_id) ; 
    tables.find(student_table_id)->second.students.insert({friend_id,friend_student}) ; 
    tables.find(friend_table_id)->second.students.insert({student_id,student}) ;
    cout<<student.name<<" switches seats with "<<friend_student.name  ; 

}
void enter(int student_id, const map<int,Table> &tables , const map<int,Students> &students)
{
    map<int,int> tables_scores  = calaulate_tables_score(student_id , tables ,students) ;
    vector<pair<int,int>> tables_scores_pair=map_to_sorted_vector(tables_scores) ; 

    for(auto& it : tables_scores_pair)
    {
        int table_id = it.first ; 
        Table table_info  = tables.find(table_id) ->second;
        int remain_capacity = table_info.capacity-table_info.students.size() ;   
        cout<<"Table "<<it.first<<": " <<remain_capacity<<" "<<table_info.queue_student.size()<<"\n" ;

    }

}

void exit(int student_id,map<int,Table> &tables , map<int,Students>&students)
{
    int student_table_id  = find_student_table(student_id , tables) ; 
    string student_name = tables[student_table_id].students[student_id].name; 
    
    tables.find(student_table_id)->second.students.erase(student_id) ;
    if(tables.find(student_table_id)->second.queue_student.size()==0)
    {
        cout <<student_name<<" exits!"  ;
        return ; 
    }
    int friend_id = students.find(student_id)->second.friend_id ;
    if(tables.find(student_table_id)->second.queue_student.find(friend_id)!=tables.find(student_table_id)->second.queue_student.end())
    {
        tables.find(student_table_id)->second.queue_student.erase(friend_id) ;
        vector<int> inputs={friend_id,student_table_id} ; 
        reserve_table(inputs , tables,students,-1) ; 
    }
    else
    {
        int student_id_replace=  tables.find(student_table_id)->second.queue_student.begin()->first ; 
        tables.find(student_table_id)->second.queue_student.erase(student_id_replace) ; 
        vector<int> inputs={student_id_replace,student_table_id} ; 
        reserve_table(inputs , tables,students,-1) ; 

    }
    
    cout <<student_name<<" exits!\n" ; 
}


vector<pair<int,int>> map_to_sorted_vector(const map<int,int>&a )
{
    vector<pair<int,int>> final ; 
    for(auto & item : a)
    {
        final.push_back(item) ; 
    }
    sort(final.begin(),final.end(),compare) ; 
    return final ; 
}
bool compare(pair<int,int> &a , pair<int,int>&b)
{
    return a.second > b.second ; 
}
void reserve_table(const vector<int> &inputs,map<int,Table> &tables , const map<int,Students> &students,int flag)
{
    int length_inputs = inputs.size() ; 
    int student_id = inputs[0] ; 
    if(length_inputs==1)
    {
        map<int,int> tables_scores  = calaulate_tables_score(student_id , tables ,students) ;
        vector<pair<int,int>> tables_scores_pair=map_to_sorted_vector(tables_scores) ; 
        int table_id = tables_scores_pair[0].first ; 
        int remain_capacity= tables.find(table_id)->second.capacity-tables.find(table_id)->second.students.size() ; 
        Students student = students.find(student_id)->second ; 
        // if(remain_capacity==0)
        // {
        //     tables.find(table_id)->second.queue_student.insert({student_id ,student}) ;
        //     cout<<student.name<<" enters the waiting queue of table "<<table_id<<"\n" ;
        // }
        if (remain_capacity>0) 
        {
            
            tables.find(table_id)->second.students.insert({student_id ,student}) ;
            // tables.find(table_id)->second.capacity = tables.find(table_id)->second.capacity -1 ;
            if(flag==0) cout<<student.name<<" sits at table "<<table_id<<"\n" ;
        } 
        else
        {
            tables.find(table_id)->second.queue_student.insert({student_id ,student}) ;
            if(flag==0) cout<<student.name<<" enters the waiting queue of table "<<table_id<<"\n" ;
        }
    }
    else
    {
        
        int table_id = inputs[1]  ; 
        int remain_capacity= tables.find(table_id)->second.capacity-tables.find(table_id)->second.students.size() ; 
        Students student = students.find(student_id)->second ; 
        // if(remain_capacity==0)
        // {
        //     tables.find(table_id)->second.queue_student.insert({student_id ,student}) ;
        //     cout<<student.name<<" enters the waiting queue of table "<<table_id<<"\n" ; 
        // }
        if (remain_capacity>0) 
        {
            tables.find(table_id)->second.students.insert({student_id ,student}) ;
            // tables.find(table_id)->second.capacity = tables.find(table_id)->second.capacity -1 ;
            if(flag==0) cout<<student.name<<" sits at table "<<table_id<<"\n" ; 
            // cout<<"iam here"<<endl;
        } 
        else
        {
            tables.find(table_id)->second.queue_student.insert({student_id ,student}) ;
            if(flag==0) cout<<student.name<<" enters the waiting queue of table "<<table_id<<"\n" ; 
            // cout<<"iam here2"<<endl;
        }
    }
}


void show_table_info (int table_id,const map<int,Table> &tables)
{
    Table table ; 
    table = tables.find(table_id)->second ; 
    int remain_cap_len= table.capacity-table.students.size()  ;
    if(remain_cap_len<0) remain_cap_len=0 ; 
    int queue_len = table.queue_student.size() ; 
    cout <<"Table ID: " << table_id <<"\n" ; 
    list<string> sorted_students_name = sort_students_name(table.students) ; 
    cout <<"People at the table: " ; 
    for(auto name:sorted_students_name)
    {
        cout<< name ; 
    }
    cout<<"\n" <<"Table remaining capacity: "<<remain_cap_len<<"\n"<<"Waiting queue length: "<<queue_len<<endl;
     
}
list<string> sort_students_name(const map<int,Students> &students)
{
    list<string> students_list ; 
    for(auto it=students.begin();it!=students.end();++it)
    {
        students_list.push_back(it->second.name);
    }
    students_list.sort() ; 
    return students_list;
}
map<int,int> calaulate_tables_score(int student_id, const map<int,Table> &tables , const map<int,Students> &students)
{
    map<int ,int> tables_scores;
    int friend_table_id = -1  , enemy_table_id=-1; 
    int friend_id =students.find(student_id)->second.friend_id ;
    friend_table_id = find_student_table(friend_id,tables) ; 
    int enemy_id = students.find(student_id)->second.enemy_id ; 
    enemy_table_id = find_student_table(enemy_id,tables) ;
    for(auto it=tables.begin() ; it!=tables.end();++it)
    {
        tables_scores.insert({it->first,calculate_one_table_score(tables , it->first , friend_table_id,enemy_table_id)}) ; 
    }
    return tables_scores ; 

    
}
int calculate_one_table_score(const map<int,Table> &tables ,int current_table_id ,int friend_table_id , int enemy_table_id )
{
    int distance_friend=0 ,distance_enemy=0, type_bonus;  
    string bonus ; 
    if(friend_table_id!=-1)
    {
        int x = abs(tables.find(current_table_id)->second.X - tables.find(friend_table_id)->second.X )  ; 
        int y  = abs(tables.find(current_table_id)->second.Y - tables.find(friend_table_id)->second.Y ) ; 
        distance_friend = x+y ; 
    }
    if(enemy_table_id!=-1)
    {
        int x = abs(tables.find(current_table_id)->second.X - tables.find(enemy_table_id)->second.X )  ; 
        int y  = abs(tables.find(current_table_id)->second.Y - tables.find(enemy_table_id)->second.Y ) ; 
        distance_enemy = x+ y ; 
    }
    bonus = tables.find(current_table_id)->second.type ; 
    if(bonus==WINDOW) type_bonus=6 ; 
    else if (bonus==DOOR) type_bonus=4 ; 
    else if (bonus==MIDDLE) type_bonus=2 ; 
    return distance_enemy - distance_friend + type_bonus ; 
}
int find_student_table(int student_id ,const map<int,Table> &tables_map)
{
    for(auto it=tables_map.begin() ; it!=tables_map.end();++it)
    {
        Table table = it->second ; 
        if(table.students.find(student_id)!=table.students.end()) return it->first   ;
    }
    return -1 ; // means student does not sit in any table yet 
}
void read_table(char * filepath,map<int,Table> &tables_map)
{
    ifstream tablesFile(filepath);
    string line ; 
    getline(tablesFile , line) ; 
    
    while(getline(tablesFile , line))
    {
        Table table ;
        
        string ID_string , X_string , Y_string , capacity_string ;  
        istringstream current_line(line) ;
        getline(current_line ,ID_string,',' ) ; 
        getline(current_line , X_string,',') ; 
        getline(current_line,Y_string,',') ; 
        getline(current_line , capacity_string ,',') ; 

        getline(current_line , table.type ) ; 
        
        table.X= stoi(X_string) ; 
        table.Y = stoi(Y_string) ; 
        table.capacity = stoi(capacity_string) ; 
        
        tables_map.insert({stoi(ID_string),table}) ;
        
    }
    
    tablesFile.close() ; 
}
void read_student(char * filepath , map<int,Students> &students_map)
{
    ifstream studentsFile(filepath);
    string line ; 
    getline(studentsFile , line) ; 
    while(getline(studentsFile , line))
    {
        Students student ;
        string ID_string ,friend_id_string ,enemy_id_string ;  
        istringstream current_line(line) ;
        getline(current_line ,ID_string,',' ) ; 
        getline(current_line , student.name,',') ; 
        getline(current_line,friend_id_string,',') ; 
        getline(current_line , enemy_id_string ) ; 
        student.friend_id= stoi(friend_id_string) ; 
        student.enemy_id = stoi(enemy_id_string) ; 
         
        students_map.insert({stoi(ID_string),student}) ; 
        
    }
    studentsFile.close();
    
}