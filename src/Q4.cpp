#include <iostream>
#include <vector>
using namespace std ; 





int main()
{
    vector<string> map ; 
    map = input_handelling() ; 

}

vector<string> input_handelling()
{
    int x , y ; 
    cin>>x>>y ; 
    vector<string> map(x) ;
    for(int i=0 ; i<x;i++)
    {
        string line ; 
        cin>>line ; 
        map[i] = line ; 
    } 
    return map ; 

}
