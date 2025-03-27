#include <iostream>

using namespace std ; 
string latex_fraction(int n,string answer="",int count=0);

int main()
{
    int n ; 
    cin>> n ;
    string a = latex_fraction(1);
    cout<<a<<endl ;
}
string latex_fraction(int n,string answer,int count)
{
    if(n==count) return answer;
    if(count==0)
    {
        answer=answer+"1";
        
    }
    return latex_fraction(n,answer,count+1) ;
}
