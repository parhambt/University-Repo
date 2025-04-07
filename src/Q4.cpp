#include <iostream>
#include <vector>
using namespace std ; 


vector<string> input_handelling(pair<int,int> &max_row_col);
vector<pair<int,int>> find_land_index(const vector<string> &map,char target,pair<int,int> max_row_col,vector<pair<int,int>> &answer,int row=0,int col=0) ;

int main()
{
    vector<string> map ; 
    pair<int,int> max_row_col=make_pair(5,5) ; 
    // map = input_handelling(max_row_col) ; 
    map = {"00111","#~%2~","0~~~~","~~%22","11222"} ;
    vector<pair<int,int>> answer ;
    auto a= find_land_index(map,'0',max_row_col,answer) ;
    int b ; 


}
vector<pair<int,int>> find_land_index(const vector<string> &map,char target,pair<int,int> max_row_col,vector<pair<int,int>> &answer,int row,int col)
{
    
    
    if(max_row_col.first==row) return answer ;
    
    if(max_row_col.second==col)
    {
        return find_land_index(map,target,max_row_col,answer,row+1 , 0) ; 
    }
    else
    {

            if(map[row][col]==target) answer.push_back(make_pair(row,col)) ; 
        return find_land_index(map,target,max_row_col,answer,row , col+1) ;
    }
    
}
vector<string> input_handelling(pair<int,int> &max_row_col)
{
    int x , y ; 
    cin>>x>>y ; 
    max_row_col.first=x ;
    max_row_col.second=y ;
    vector<string> map(x) ;
    for(int i=0 ; i<x;i++)
    {
        string line ; 
        cin>>line ; 
        map[i] = line ; 
    } 
    return map ; 

}
