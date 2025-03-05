#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std ; 
typedef struct Table Table ; 
typedef struct Students Students ; 

void read_table(char * filepath,list<Table> &tables) ; 
void read_student(char * filepath , list<Students> &students) ;

typedef struct Table
{
    int ID ; 
    int X ; 
    int Y ; 
    int capacity ; 
    string type ; 

}Table ; 

typedef struct Students
{
    int ID ; 
    string name ; 
    int friend_id ;
    int enemy_id ;  
}Students ; 

int main(int argc , char * argv[])
{
    list<Table> tables; 
    list<Students> students ; 
    read_table(argv[0],tables) ; 
    read_student(argv[1],students) ; 
    
}
int calaulate_table_score()
{

}
void read_table(char * filepath,list<Table> &tables)
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
        table.ID = stoi(ID_string) ; 
        table.X= stoi(X_string) ; 
        table.Y = stoi(Y_string) ; 
        table.capacity = stoi(capacity_string) ; 
        tables.push_back(table) ; 
        
    }
}
void read_student(char * filepath , list<Students> &students)
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
         
        student.ID = stoi(ID_string) ; 
        student.friend_id= stoi(friend_id_string) ; 
        student.enemy_id = stoi(enemy_id_string) ; 
         
        students.push_back(student) ; 
        
    }
}