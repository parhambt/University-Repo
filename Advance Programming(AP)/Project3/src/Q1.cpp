#include <iostream>

using namespace std ; 
string latex_fraction(int n,string answer="",int count=1,int number=1);

int main()
{
    int n ; 
    cin>> n ;
    string a = latex_fraction(n);
    cout<<a<<endl ;
}
string latex_fraction(int n,string answer,int count,int number)
{
    if(n==count) return to_string(number);
    if(n==1)
    {
        return to_string(number);
    }
    if(count==1) answer=answer+to_string(number);
    string numerator=latex_fraction(n,answer,count+1,number*2);
    string denumerator=latex_fraction(n,answer,count+1,(number*2)+1);
    return to_string(number)+"+\\frac{"+numerator+"}{"+denumerator+"}";
}
