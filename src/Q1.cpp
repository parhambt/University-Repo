#include <iostream>

using namespace std ; 
string latex_fraction(int n,string answer="",int count=0);

int main()
{
    int n ; 
    cin>> n ;
    string a = latex_fraction(n);
    cout<<a<<endl ;
}
string latex_fraction(int n,string answer,int count)
{
    if(n==count) return answer;
    if(count==0)
    {
        answer=answer+"1";
    }
    string numerator=latex_fraction(2*count,answer,count+1);
    string denumerator=latex_fraction((2*count)+1,answer,count+1);
    return answer+to_string(count)+"+\frac{"+numerator+"}{"+denumerator+"}";
}
