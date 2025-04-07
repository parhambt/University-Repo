#include <iostream>
#include <vector>
using namespace std ; 

const char SEA='~' ; 
const char MOUNTAIN='#' ;
const char SEAPORT='%' ;
const vector<char> LANDS = {'0','1','2','3','4','5','6','7','8','9'} ;

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
void find_direction(const vector<string> &map , const vector<pair<int,int>> &targget_land_index ,pair<int,int> current_index,char target,vector<vector<pair<int,int>>> all_direction , vector<pair<int,int>> one_direction)
{
    vector<char> possible_path=find_possible_path(current_index,map,target) ;
    if()
}
vector<char> find_possible_path(pair<int,int> current_index,const vector<string> &map,char target)
{
    vector<char> avaleble_path ; 
    auto is_land=[](pair<int,int> current_index , const vector<string> &map)
    {
        if(map[current_index.first][current_index.second]>=48 && map[current_index.first][current_index.second]<=57) return true ; 
        else return false ; 
    } ;

    if(is_land(current_index,map)) // it is in land
    {
        avaleble_path.push_back(target) ; 
        avaleble_path.push_back(SEAPORT) ;
    }
    else if(map[current_index.first][current_index.second]==SEAPORT)// it is not currently on land
    {
        avaleble_path.push_back(SEA) ;
        avaleble_path.push_back(target) ;
        avaleble_path.push_back(SEAPORT) ; 
    }
    else if(map[current_index.first][current_index.second]==SEA)
    {
        avaleble_path.push_back(SEAPORT) ; 
        avaleble_path.push_back(SEA) ;
    }
    return avaleble_path ;
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
