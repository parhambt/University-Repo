#include <iostream>
#include <vector>
using namespace std ;
int find_oldest_index(const vector<int> &ages,int oldest_index=0,int cur_index=0);
int main()
{
    vector<int> ages={1,4,3,2,5};
    cout<<find_oldest_index(ages)<<endl ;
}
int find_oldest_index(const vector<int> &ages,int oldest_index,int cur_index)
{
    if(ages.size()==cur_index) return oldest_index ;
    if(ages[cur_index]>ages[oldest_index]) oldest_index=cur_index ;
    return find_oldest_index(ages,oldest_index,cur_index+1);
}
