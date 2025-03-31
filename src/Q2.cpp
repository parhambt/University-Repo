#include <iostream>
#include <vector>
using namespace std ;
int find_oldest_index(const vector<int> &ages,int oldest_index=0,int cur_index=0);
void input_handelling(vector<int> &ages,vector<pair<int,int>>&money);
int find_lesser_itself_biggest_other(const vector<int>&ages,int compare_value,int biggest_index=-1 , int cur_index=0 );
void apply_situation_condition(int left_side_getMoney_index,int right_side_getMoney_index,int oldest_index,vector<pair<int,int>> &money );
void distribute_money(vector<int>ages,vector<pair<int,int>> &money,int oldest_index);
void output_handelling(const vector<pair<int,int>>&moneys);
int main()
{
    vector<int> ages={1,4,3,2,5};
    vector<pair<int,int>> money={pair(2,0),pair(2,0),pair(2,0),pair(2,0),pair(2,0)};
    //in first index of pair is him money can be given to some one else and the seconed index can not given to any one
    // input_handelling(ages,money);
    distribute_money(ages,money,find_oldest_index(ages));
    output_handelling(money);

}
void distribute_money(vector<int>ages,vector<pair<int,int>> &money,int oldest_index)
{
    if(oldest_index==-1) return;
    vector<int> sub_left(ages.begin(), ages.begin() + oldest_index);
    vector<int> sub_right(ages.begin()+oldest_index+1,ages.end());
    int left_side_getMoney_index_start=find_lesser_itself_biggest_other(sub_left,ages[oldest_index]);
    int right_side_getMoney_index_start=find_lesser_itself_biggest_other(sub_right,ages[oldest_index]);
    apply_situation_condition(left_side_getMoney_index_start,right_side_getMoney_index_start,oldest_index,money);
    ages.erase(ages.begin()+oldest_index);
    distribute_money(ages,money,left_side_getMoney_index_start);
    distribute_money(ages,money,right_side_getMoney_index_start);
}
void apply_situation_condition(int left_side_getMoney_index,int right_side_getMoney_index,int oldest_index,vector<pair<int,int>> &money )
{
    if(left_side_getMoney_index!=-1 &&right_side_getMoney_index!=-1)
    {
        int money_shared=(money[oldest_index].first)/2;
        money[left_side_getMoney_index].second+=money_shared;
        money[right_side_getMoney_index+1+oldest_index].second+=money_shared;
    }
    else if(left_side_getMoney_index!=-1 &&right_side_getMoney_index==-1)
    {
        int money_shared=(money[oldest_index].first);
        money[left_side_getMoney_index].second+=money_shared;
    }
    else if(left_side_getMoney_index==-1 &&right_side_getMoney_index!=-1)
    {
        int money_shared=(money[oldest_index].first);
        money[right_side_getMoney_index+1+oldest_index].second+=money_shared;
    }
    else
    {
        int money_shared=(money[oldest_index].first);
        money[oldest_index].second+=money_shared;
    }
    money[oldest_index].first=0;

}
int find_oldest_index(const vector<int> &ages,int oldest_index,int cur_index)
{
    if(ages.size()==cur_index) return oldest_index ;
    if(ages[cur_index]>ages[oldest_index]) oldest_index=cur_index ;
    return find_oldest_index(ages,oldest_index,cur_index+1);
}
int find_lesser_itself_biggest_other(const vector<int>&ages,int compare_value,int biggest_index , int cur_index )
{
    if(cur_index==ages.size()) return biggest_index ; // -1 means there is no number with that condition
    if(biggest_index==-1)
    {
        if(compare_value>ages[cur_index]) biggest_index=cur_index ;
    }
    else
    {
        if(compare_value>ages[cur_index]&& ages[cur_index]>ages[biggest_index]) biggest_index=cur_index;
    }
    return find_lesser_itself_biggest_other(ages,compare_value,biggest_index,cur_index+1);
}
void input_handelling(vector<int> &ages,vector<pair<int,int>>&money)
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
            else money.push_back(pair(tmp,0));
        }  
    }
}
void output_handelling(const vector<pair<int,int>>&moneys)
{
    int i=0;
    for(auto& money:moneys)
    {
        if(moneys.size()-1==i) cout<<money.first+money.second;
        else cout<<money.first+money.second<<" ";
        i++;
    }
}
