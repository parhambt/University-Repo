#include <iostream>
#include <vector>
using namespace std ;
int find_oldest_index(const vector<int> &ages,int oldest_index=0,int cur_index=0);
void input_handelling(vector<int> &ages,vector<int>&money);
int main()
{
    vector<int> ages;
    vector<int> money ;
    input_handelling(ages,money);

}
int find_oldest_index(const vector<int> &ages,int oldest_index,int cur_index)
{
    if(ages.size()==cur_index) return oldest_index ;
    if(ages[cur_index]>ages[oldest_index]) oldest_index=cur_index ;
    return find_oldest_index(ages,oldest_index,cur_index+1);
}
void input_handelling(vector<int> &ages,vector<int>&money)
{
    int person_number ;
    cin>>person_number;
    
    for(int i=0 ; i<2;i++)
    {
        for(int j=0;j<person_number;j++)
        {
            int tmp ;
            cin>>tmp ;
            if(i==0) ages.push_back(tmp);
            else money.push_back(tmp);
        }  
    }
}
