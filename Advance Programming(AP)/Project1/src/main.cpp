#include <iostream> 
#include <string> 
#include <vector>
#include <map>
#include <list>
#include <bits/stdc++.h>
using namespace std ;

typedef struct Employee Employee  ;
typedef struct Task Task  ;

Task add_task(string task_name ,int priority ) ; 
Employee add_employee(string employee_name);
void assign_employee (string task_name , string employee_name , vector<Task> &tasks , vector<Employee> &employee) ;
void finish_task(string task_name,vector<Task> &tasks,vector<Employee> &Employees);
void report_all(vector<Task> tasks) ; 
void report_ongoing(vector<Task> tasks) ; 
void report_employee(string employee_name,vector<Employee> employees);
void input_handeling(string line ,vector <Task> &tasks ,vector<Employee> &employes ) ;
const string add_task_name = "add_task" ; 
const string add_employee_name = "add_employee" ; 
const string assign_employee_name = "assign_employee" ; 
const string finish_task_name = "finish_task" ; 
const string report_name = "report" ; 
const string all_name = "all" ;
const string ongoing_name = "ongoing" ; 
const string Employee_name= "employee" ; 
const string TODO ="TODO" ; 
const string ONGOING="ONGOING" ; 
const string DONE = "DONE" ; 
typedef struct Employee
{
    string employee_name  ;
    vector<Task> tasks ; 
}Employee ; 
typedef struct Task
{
    string task_name ; 
    int priority ; 
    vector<Employee> employees ; 
    string status ; 
}Task;

int main()
{
    string line ; 
    vector <Task> tasks ; 
    vector<Employee> employes; 
    input_handeling(line ,tasks , employes);
    
}
void input_handeling(string line ,vector <Task> &tasks ,vector<Employee> &employes )
{
    while(getline(cin ,line))
    {
        
        std::regex del(" ")  ;
        sregex_token_iterator it(line.begin(),line.end(),del,-1) ; 
        sregex_token_iterator end ; 
        if(*it==add_task_name)
        {
            ++it ; 
            string arg1 = *it ; 
            ++it ;
            int arg2 = stoi(*it) ; 
            tasks.push_back(add_task(arg1 , arg2)) ; 
        }
        else if (*it==add_employee_name)
        {
            ++it ; 
            string arg1 = *it ;
            employes.push_back(add_employee(arg1)) ;
        }
        else if (*it==assign_employee_name)
        {
            ++it ; 
            string arg1 = *it ;
            ++it ; 
            string arg2 = *it ;
            assign_employee(arg1 , arg2,tasks,employes) ; 
        }
        else if (*it==finish_task_name)
        {
            ++it ; 
            string arg1 = *it ;
            finish_task(arg1,tasks,employes);
        }
        else if(*it==report_name)
        {
            ++it ; 
            if(*it==all_name)
            {
                report_all(tasks) ;
            }
            else if (*it==ongoing_name)
            {
                report_ongoing(tasks) ;
            }
            else if (*it==Employee_name)
            {
                ++it ; 
                string arg1 = *it ;
                report_employee(arg1 ,employes) ;                
            }
        }

    }
}
Task add_task(string task_name ,int priority )
{
    Task task ; 
    task.task_name = task_name ; 
    task.priority = priority ; 
    task.status = TODO ; 
    return task ; 
}
Employee add_employee(string employee_name)
{
    Employee employee ; 
    employee.employee_name = employee_name ; 
    return employee ;
}
void assign_employee (string task_name , string employee_name , vector<Task> &tasks , vector<Employee> &employees)
{
    vector<Task>::iterator it ; 
    Employee employee ; 
    employee.employee_name=employee_name ;
    for(it=tasks.begin();it!=tasks.end() ; ++it)
    {
        if(it->task_name == task_name)
        {
            (it->employees).push_back(employee) ;
            it->status=ONGOING ;
            break;
        }
    }
    vector<Employee>::iterator it_1 ; 
    for(it_1=employees.begin();it_1!=employees.end() ; ++it_1)
    {
        if(it_1->employee_name==employee_name)
        {
            (it_1->tasks).push_back(*it) ; 
            break; 
        }
    }

}
void finish_task(string task_name,vector<Task> &tasks,vector<Employee> &employees)
{
    vector<Task>::iterator it ; 
    for(it=tasks.begin();it!=tasks.end();++it)
    {
        if(it->task_name==task_name)
        {
            it->status=DONE ;
            break;
        }
    }
    vector<Employee>::iterator it_1 ;
    vector<Task>::iterator it_2 ; 
    for(it_1 = employees.begin(); it_1!=employees.end();++it_1) 
    {
        for(it_2 =it_1->tasks.begin() ; it_2!=it_1->tasks.end();++it_2)
        {
            if(it_2->task_name == task_name)
            {
                it_2->status = DONE ; 
            }
        }
    }
}
void report_all(vector<Task> tasks)
{
    int todo=0 ,ongoing=0 , done=0 ; 
    for(Task task : tasks)
    {
        if(task.status==TODO) todo++ ; 
        else if (task.status==ONGOING) ongoing ++ ; 
        else if (task.status==DONE) done ++ ;
    }
    cout <<"TODO: "<<todo <<"\n"<<"ONGOING: "<<ongoing<<"\n"<<"DONE: "<<done<<endl ;
}
void report_ongoing(vector<Task> tasks)
{
    auto sort_by_priority = [](const Task &task1 , const Task &task2)
     {if(task1.priority==task2.priority) return task1.task_name < task2.task_name ; 
    else return task1.priority<task2.priority ;  } ; 
    auto sort_by_name = [](const Employee &e1 , const Employee &e2){return e1.employee_name < e2.employee_name ;} ;
    sort(tasks.begin(),tasks.end(),sort_by_priority) ;
    for(Task task : tasks)
    {
        if(task.status==ONGOING)
        {
            sort((task.employees).begin(),(task.employees).end(),sort_by_name) ;
            cout<< task.task_name <<" ("<<task.priority<<"): " ;
            vector<Employee>::const_iterator it ; 
            for(it=(task.employees).begin() ; it!=(task.employees).end() ; ++it)
            {
                if((it+1) == (task.employees).end())
                {
                    cout << it->employee_name ; 
                }
                else 
                {
                    cout << it->employee_name <<", " ; 
                }
            } 
            cout<<"\n" ; 
        }
    }
    
}
void report_employee(string employee_name,vector<Employee> employees)
{
    int count_task=0,count_ongoing=0 ; 
    bool flag = false ; 

    for(Employee e:employees)
    {
        if(e.employee_name==employee_name)
        {
            for(Task task:e.tasks)
            {
                if(task.status==DONE) count_task++ ; 
            }
            
            cout << employee_name <<" has done "<<count_task<<" tasks."<<"\n" ;
            vector<Task>::const_iterator it ; 
            for(it=(e.tasks).begin();it!=(e.tasks).end();++it)
            {
                if(it->status==ONGOING)
                {
                    count_ongoing++ ;
                     
                    if(flag==false) cout<<employee_name<<" is currently working on these tasks:"<<"\n" ;
                    cout<<count_ongoing<<". "<<it->task_name<<"\n" ;

                    flag=true ;
                }
            }
            if(flag==false) cout<<employee_name<<" is currently not working on any tasks."<<"\n" ; 
        }
    }
}