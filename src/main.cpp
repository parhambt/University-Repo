#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std ; 

const string WINDOW = "window" ; 
const string DOOR = "door" ; 
const string MIDDLE = "middle" ; 

typedef struct Table Table ; 
typedef struct Students Students ; 

void read_table(char * filepath,map<int,Table> &tables) ; 
void read_student(char * filepath , map<int,Students> &students_map) ; 
int find_student_table(int student_id , const map<int,Table> &tables_map) ; 

typedef struct Table
{
    // int ID ; 
    int X ; 
    int Y ; 
    int capacity ; 
    string type ; 
    map<int,Students> students ; 

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
    read_table(argv[0],tables) ; 
    read_student(argv[1],students) ; 
    
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
        getline(current_line , table.type , ',') ; 
        
        table.X= stoi(X_string) ; 
        table.Y = stoi(Y_string) ; 
        table.capacity = stoi(capacity_string) ; 
        // map.insert( {stoi(ID_string) , table}) ; 
        tables_map.insert({stoi(ID_string),table}) ;
        
    }
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
        getline(current_line , enemy_id_string ,',') ; 
         
        
        student.friend_id= stoi(friend_id_string) ; 
        student.enemy_id = stoi(enemy_id_string) ; 
         
        students_map.insert({stoi(ID_string),student}) ; 
        
    }
}