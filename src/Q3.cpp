#include <iostream>
#include <vector>
#include <map>
using namespace std ; 
const int TAX=10 ;

void input_handelling(map<string,int> &info,map<string,int> &menu_map , vector<string> &menu_list);
int sumBill(map<string,int> menu , vector<string> input,bool &flag,map<string,int> count_item)  ; 
void allPosibelityOrder(map<string,int> &menu_map,vector<string> menu_list,vector<pair<vector<string>,int>> &all_posiblities,vector<string> possibelity={},int possibelity_price=0) ;
pair<int,int> findBoundPrice( map<string,int> &info) ; 
void checkCondition(map<string,int> info,map<string,int> menu_map , const vector<pair<vector<string>,int>> &all_posiblities,pair<int,int> price_bound,pair<vector<string>,int> &answer, int index=0 ) ; 
void output_handelling(const vector<string> &foods ) ;

int main()
{
    // map<string,int> info={{"count_menu",3},{"discount%",50},{"least_money_discountApply",500},{"max_discount_value",310}};
    // map<string,int> menu_map={{"Juicy_burger",250},{"Fettuccine_Alfredo",300},{"Coca_Cola",30}} ;
    // vector<string> menu_list={"Juicy_burger","Fettuccine_Alfredo","Coca_Cola"} ; 
    map<string,int> info;
    map<string,int> menu_map;
    vector<string> menu_list ; 
    input_handelling(info,menu_map,menu_list);
    vector<pair<vector<string>,int>> all_posiblities ;
    allPosibelityOrder(menu_map,menu_list,all_posiblities) ; 
    pair<vector<string>,int> best_order = {{},-1} ; 
    pair<int,int> price_bound = findBoundPrice(info) ; 
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
void checkCondition(map<string,int> info,map<string,int> menu_map , const vector<pair<vector<string>,int>> &all_posiblities,pair<int,int> price_bound,pair<vector<string>,int> &answer, int index )
{
    if(index == all_posiblities.size()) return ; 
    int bill =all_posiblities[index].second ; 
    bill += bill/10 ; 
    if(bill>=price_bound.first && bill<=price_bound.second && bill>answer.second) answer = all_posiblities[index] ; 
    checkCondition(info , menu_map , all_posiblities , price_bound , answer , index+1) ; 

}
pair<int,int> findBoundPrice( map<string,int> &info)
{
    int low_bound = info["least_money_discountApply"] ;
    double ratio = info["discount%"]/100.0 ; 
    int up_bound = (1/ratio) * (info["max_discount_value"]) ; 
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
void output_handelling(const vector<string> &foods )
{
    for(auto& food:foods)
    {
        cout<<food<<endl ;
    } 

}
