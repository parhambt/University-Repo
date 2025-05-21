#include <iostream>
#include <vector>
using namespace std ;
int find_oldest_index(const vector<int> &ages, int start_index, int end_index,int biggest_index) ;
void input_handelling(vector<int> &ages,vector<pair<int,int>>&money);
int find_lesser_itself_biggest_other(const vector<int>& ages, int compare_value, int start_index, int end_index,int biggest_index=-1);
void apply_situation_condition(int left_side_getMoney_index,int right_side_getMoney_index,int oldest_index,vector<pair<int,int>> &money );
void distribute_money(const vector<int>& ages, vector<pair<int,int>> &money, int start, int end);
void output_handelling(const vector<pair<int,int>>&moneys);
int main()
{
    vector<int> ages;
    vector<pair<int,int>> money;
    input_handelling(ages,money);
    distribute_money(ages, money, 0, ages.size()-1);
    output_handelling(money);
}

void distribute_money(const vector<int>& ages, vector<pair<int,int>> &money, int start, int end) {
    if (start > end) return;
    int oldest_index = find_oldest_index(ages, start, end,start);
    int left_index = find_lesser_itself_biggest_other(ages, ages[oldest_index], start, oldest_index - 1);
    int right_index = find_lesser_itself_biggest_other(ages, ages[oldest_index], oldest_index + 1, end);
    apply_situation_condition(left_index, right_index, oldest_index, money);
    distribute_money(ages, money, start, oldest_index - 1);
    distribute_money(ages, money, oldest_index + 1, end);
}
void apply_situation_condition(int left_side_getMoney_index,int right_side_getMoney_index,int oldest_index,vector<pair<int,int>> &money )
{
    if(left_side_getMoney_index!=-1 && right_side_getMoney_index!=-1)
    {
        int money_shared=(money[oldest_index].first)/2;
        money[left_side_getMoney_index].second+=money_shared;
        money[right_side_getMoney_index].second+=money_shared;
    }
    else if(left_side_getMoney_index!=-1 && right_side_getMoney_index==-1)
    {
        int money_shared=(money[oldest_index].first);
        money[left_side_getMoney_index].second+=money_shared;
    }
    else if(left_side_getMoney_index==-1 && right_side_getMoney_index!=-1)
    {
        int money_shared=(money[oldest_index].first);
        money[right_side_getMoney_index].second+=money_shared;
    }
    else
    {
        int money_shared=(money[oldest_index].first);
        money[oldest_index].second+=money_shared;
    }
    money[oldest_index].first=0;

}
int find_oldest_index(const vector<int> &ages, int start_index, int end_index,int biggest_index) 
{
    if(start_index>end_index) return biggest_index;
    if(ages[start_index]>ages[biggest_index]) biggest_index=start_index ;
    return find_oldest_index(ages,start_index+1,end_index,biggest_index);
}
int find_lesser_itself_biggest_other(const vector<int>& ages, int compare_value, int start_index, int end_index,int biggest_index)
{
    if(start_index>end_index) return biggest_index ;
    if(biggest_index==-1)
    {
        if(compare_value>ages[start_index]) biggest_index=start_index ;
    }
    else
    {
        if(compare_value>ages[start_index]&& ages[start_index]>ages[biggest_index]) biggest_index=start_index;
    }
    return find_lesser_itself_biggest_other(ages,compare_value,start_index+1,end_index,biggest_index);
    
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
    cout<<endl ; 
}
