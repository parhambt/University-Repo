#include <iostream>
#include <vector>
#include <map>
using namespace std ; 
const int TAX=10 ;
const string COUNTMENUE="count_menu" ; 
const string DISCOUNT="discount%" ; 
const string LEASTDISCOUNT="least_money_discountApply" ; 
const string MAXDISCOUNT="max_discount_value" ; 

void input_handelling(map<string,int> &info,map<string,int> &menu_map , vector<string> &menu_list);
int sumBill(map<string,int> menu , vector<string> input,bool &flag,map<string,int> count_item)  ; 
void allPosibelityOrder(map<string,int> &menu_map,vector<string> menu_list,vector<pair<vector<string>,int>> &all_posiblities,vector<string> possibelity={},int possibelity_price=0) ;
pair<int,double> findBoundPrice( map<string,int> &info) ; 
void checkCondition(map<string,int> info,map<string,int> menu_map , const vector<pair<vector<string>,int>> &all_posiblities,pair<int,double> price_bound,pair<vector<string>,int> &answer, int index=0 ) ; 
void output_handelling(const vector<string> &foods ) ;

int main()
{

    map<string,int> info;
    map<string,int> menu_map;
    vector<string> menu_list ; 
    input_handelling(info,menu_map,menu_list);
    vector<pair<vector<string>,int>> all_posiblities ;
    allPosibelityOrder(menu_map,menu_list,all_posiblities) ; 
    pair<vector<string>,int> best_order = {{},-1} ; 
    pair<int,double> price_bound = findBoundPrice(info) ; 
    checkCondition(info,menu_map,all_posiblities,price_bound,best_order) ;
    output_handelling(best_order.first) ;
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
void checkCondition(map<string,int> info,map<string,int> menu_map , const vector<pair<vector<string>,int>> &all_posiblities,pair<int,double> price_bound,pair<vector<string>,int> &answer, int index )
{
    if(index == all_posiblities.size()) return ; 
    double bill =all_posiblities[index].second ; 
    bill += bill/10 ; 
    if(bill>=price_bound.first && bill<=price_bound.second && bill>answer.second) answer = all_posiblities[index] ; 
    checkCondition(info , menu_map , all_posiblities , price_bound , answer , index+1) ; 

}
pair<int,double> findBoundPrice( map<string,int> &info)
{
    int low_bound = info[LEASTDISCOUNT] ;
    double ratio = info[DISCOUNT]/100.0 ; 
    double up_bound = (1/ratio) * (info[MAXDISCOUNT]) ; 
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
    info.insert({COUNTMENUE,n}) ; info.insert({DISCOUNT,x}) ;
    info.insert({LEASTDISCOUNT,l}) ; info.insert({MAXDISCOUNT,r}) ;
    for(int i=0 ; i<n;i++)
    {
        string food_name ; 
        int price ; 
        cin>>food_name>>price ;
        menu_map.insert({food_name,price});
        menu_list.push_back(food_name);
    }

}
void output_handelling(const vector<string> &foods )
{
    for(auto& food:foods)
    {
        cout<<food<<endl ;
    } 

}
