#include <iostream>
#include <vector>
#include <map>
using namespace std ; 
const int TAX=10 ;

void input_handelling(map<string,int> &info,map<string,int> &menu_map , vector<string> &menu_list);
int sumBill(map<string,int> menu , vector<string> input,bool &flag,map<string,int> count_item)  ; 

int main()
{
    map<string,int> info;
    map<string,int> menu_map ;
    vector<string> menu_list ; 
    input_handelling(info,menu_map,menu_list);
}



int sumBill(map<string,int> menu , vector<string> input,bool &flag,map<string,int> count_item)
{
    if(input.size()==1)
    {
        string item = input[0] ;
        return menu[item] ;
    }
    string item = input[0] ; 
    
    if(count_item.find(item)!=count_item.end()) flag=false ;
    count_item.insert({item,1}) ;

    input.erase(input.begin());
    return menu[item]+sumBill(menu,input,flag,count_item);

}
void input_handelling(map<string,int> &info,map<string,int> &menu_map , vector<string> &menu_list)
{
    int n,x,l,r ; 
    cin>>n>>x>>l>>r ; 
    info.insert({"count_menu",n}) ; info.insert({"discount%",x}) ;
    info.insert({"least_money_discountApply",l}) ; info.insert({"max_discount_value",r}) ;
    for(int i=0 ; i<n;i++)
    {
        string food_name ; 
        int price ; 
        cin>>food_name>>price ;
        menu_map.insert({food_name,price});
        menu_list.push_back(food_name);
    }

}
