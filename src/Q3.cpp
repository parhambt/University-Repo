#include <iostream>
#include <vector>
#include <map>
using namespace std ; 
const int TAX=10 ;

void input_handelling(map<string,int> &info,map<string,int> &menu_map , vector<string> &menu_list);
int sumBill(map<string,int> menu , vector<string> input,bool &flag,map<string,int> count_item)  ; 
void allPosibelityOrder(map<string,int> &menu_map,vector<string> menu_list,vector<pair<vector<string>,int>> &all_posiblities,vector<string> possibelity={},int possibelity_price=0) ;

int main()
{
    map<string,int> info;
    map<string,int> menu_map ;
    vector<string> menu_list ; 
    input_handelling(info,menu_map,menu_list);
   

}
void allPosibelityOrder(map<string,int> &menu_map,vector<string> menu_list,vector<pair<vector<string>,int>> &all_posiblities,vector<string> possibelity,int possibelity_price)
{
    if(menu_list.empty())
    {
        if(possibelity.empty()==false)
            all_posiblities.push_back(make_pair(possibelity,possibelity_price)) ; 
        return ; 
    }
    string target = menu_list[0] ;
    int price_target=menu_map[target] ;
    menu_list.erase(menu_list.begin());
    allPosibelityOrder(menu_map,menu_list,all_posiblities,possibelity,possibelity_price);
    possibelity.push_back(target);
    allPosibelityOrder(menu_map,menu_list,all_posiblities,possibelity,possibelity_price+price_target);

}
vector<string> checkMaxDiscountCondition(map<string,int> info,map<string,int> menu , const vector<string> &input1,const vector<string> &input2  )
{


}
pair<int,int> findBoundPrice( map<string,int> &info)
{
    int low_bound = info["least_money_discountApply"] ;
    int up_bound = (1/(info["discount%"]/100)) * (info["max_discount_value"]) ; 
    return make_pair(low_bound,up_bound) ;
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
