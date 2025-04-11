#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const char SEA = '~';
const char MOUNTAIN = '#';
const char SEAPORT = '%';
const vector<char> LANDS = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

vector<string> input_handelling(pair<int, int> &max_row_col);
vector<pair<int, int>> find_land_index(const vector<string> &map, char target, pair<int, int> max_row_col, vector<pair<int, int>> &answer, int row = 0, int col = 0);
void find_path(const vector<string> &map, vector<pair<int, int>> &targget_land_index, pair<int, int> max_row_col, pair<int, int> current_index,pair<int, int> start_index, char target, vector<vector<pair<int, int>>> &all_direction, vector<pair<int, int>> &one_direction, vector<pair<int, int>> &block_index,bool is_target_land_use=false);
bool is_avaleble_direction(const vector<string> &map, vector<char> possible_path, pair<int, int> possible_next_direction);
vector<char> find_possible_place(pair<int, int> current_index, const vector<string> &map, char target);

int main()
{
    vector<string> map;
    pair<int, int> max_row_col = make_pair(5, 5);
    // map = input_handelling(max_row_col) ;
    map = {"00111", "#~%2~", "0~~~~", "~~%22", "11222"};
    vector<pair<int, int>> answer;
    vector<vector<pair<int, int>>> all_direction;
    vector<pair<int, int>> one_direction, block_index;
    bool is_end=true ; 
    auto target_land_index = find_land_index(map, '2', max_row_col, answer);
    
    find_path(map, target_land_index, max_row_col, target_land_index[0],target_land_index[0], '2', all_direction, one_direction, block_index,false);
    int b;
}
void find_path(const vector<string> &map,  vector<pair<int, int>> &targget_land_index, pair<int, int> max_row_col, pair<int, int> current_index,pair<int, int> start_index, char target, vector<vector<pair<int, int>>> &all_direction, vector<pair<int, int>> &one_direction, vector<pair<int, int>> &block_index,bool is_target_land_use)
{

    if(targget_land_index.empty() ) return ; 

    
    bool is_end = true ; 
    //checking is curent index exist in target_land ? 
    if (find(targget_land_index.begin(), targget_land_index.end(), current_index) != targget_land_index.end())
        targget_land_index.erase(find(targget_land_index.begin(), targget_land_index.end(), current_index));

    if (find(block_index.begin(), block_index.end(), current_index) != block_index.end()) // check this curent cord valid or not
        return;

    one_direction.push_back(current_index);
    block_index.push_back(current_index);


    pair<int, int> possible_next_direction;
    vector<char> possible_path = find_possible_place(current_index, map, target);

    auto is_invalid_index = [&possible_next_direction, &block_index](pair<int, int> current_index, pair<int, int> add_direction, const pair<int, int> &max_row_col)
    {
        current_index.first += add_direction.first;
        current_index.second += add_direction.second;
        possible_next_direction = current_index;

        if (current_index.first < 0 || current_index.second < 0 ||
            current_index.first >= max_row_col.first || current_index.second >= max_row_col.second)
            return false;

        if (find(block_index.begin(), block_index.end(), current_index) != block_index.end())
            return false;

        return true;
    };

    // Right
    if (is_invalid_index(current_index, make_pair(0, 1), max_row_col))
    {
        if (is_avaleble_direction(map, possible_path, possible_next_direction))
        {
            is_end = false ; 
            find_path(map, targget_land_index, max_row_col, possible_next_direction,start_index, target, all_direction, one_direction, block_index,true);
  
        }
    }
    // Down
    if (is_invalid_index(current_index, make_pair(1, 0), max_row_col))
    {
        if (is_avaleble_direction(map, possible_path, possible_next_direction))
        {
            is_end = false ; 
            find_path(map, targget_land_index, max_row_col, possible_next_direction,start_index, target, all_direction, one_direction, block_index,true);

        }
    }
    // Left
    if (is_invalid_index(current_index, make_pair(0, -1), max_row_col))
    {
        if (is_avaleble_direction(map, possible_path, possible_next_direction))
        {
            is_end = false ; 
            find_path(map, targget_land_index, max_row_col, possible_next_direction,start_index, target, all_direction, one_direction, block_index,true);
             

             
        }
    }
    // Up
    if (is_invalid_index(current_index, make_pair(-1, 0), max_row_col))
    {
        if (is_avaleble_direction(map, possible_path, possible_next_direction))
        {
            is_end =false ;
            find_path(map, targget_land_index, max_row_col, possible_next_direction,start_index, target, all_direction, one_direction, block_index,true);
            
        }
    }
    if(map[current_index.first][current_index.second]==target && is_end)
        all_direction.push_back(one_direction) ; 
    one_direction.pop_back();
    block_index.pop_back();
    if( current_index==start_index) 
    find_path(map, targget_land_index, max_row_col, targget_land_index[0],targget_land_index[0], target, all_direction, one_direction, block_index,false);


}

bool is_avaleble_direction(const vector<string> &map, vector<char> possible_path, pair<int, int> possible_next_direction)
{
    if (possible_path.size() == 1)
    {
        if (map[possible_next_direction.first][possible_next_direction.second] == possible_path[0])
            return true;
        else
            return false;
    }
    if (map[possible_next_direction.first][possible_next_direction.second] == possible_path[0])
        return true;
    possible_path.erase(possible_path.begin());
    return is_avaleble_direction(map, possible_path, possible_next_direction);
}
vector<char> find_possible_place(pair<int, int> current_index, const vector<string> &map, char target)
{
    vector<char> avaleble_path;
    auto is_land = [](pair<int, int> current_index, const vector<string> &map)
    {
        if (map[current_index.first][current_index.second] >= 48 && map[current_index.first][current_index.second] <= 57)
            return true;
        else
            return false;
    };

    if (is_land(current_index, map)) // it is in land
    {
        avaleble_path.push_back(target);
        avaleble_path.push_back(SEAPORT);
    }
    else if (map[current_index.first][current_index.second] == SEAPORT) // it is not currently on land
    {
        avaleble_path.push_back(SEA);
        avaleble_path.push_back(target);
        avaleble_path.push_back(SEAPORT);
    }
    else if (map[current_index.first][current_index.second] == SEA)
    {
        avaleble_path.push_back(SEAPORT);
        avaleble_path.push_back(SEA);
    }
    return avaleble_path;
}
vector<pair<int, int>> find_land_index(const vector<string> &map, char target, pair<int, int> max_row_col, vector<pair<int, int>> &answer, int row, int col)
{

    if (max_row_col.first == row)
        return answer;

    if (max_row_col.second == col)
    {
        return find_land_index(map, target, max_row_col, answer, row + 1, 0);
    }
    else
    {

        if (map[row][col] == target)
            answer.push_back(make_pair(row, col));
        return find_land_index(map, target, max_row_col, answer, row, col + 1);
    }
}
vector<string> input_handelling(pair<int, int> &max_row_col)
{
    int x, y;
    cin >> x >> y;
    max_row_col.first = x;
    max_row_col.second = y;
    vector<string> map(x);
    for (int i = 0; i < x; i++)
    {
        string line;
        cin >> line;
        map[i] = line;
    }
    return map;
}
