/// http://adventofcode.com/2017/day/21
/// liuyubobobo
/// 2018-02-27

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;


class Solution{

private:
    unordered_map<string, string> rules;

public:
    int pixel_num(int iter, const vector<string>& raw_rules){

        get_rules(raw_rules);
        // cout << rules.size() << endl;
        // print_rules();

        string cur_s = ".#./..#/###";
        for(int i = 0 ; i < iter ; i ++)
            cur_s = change(cur_s);

        int res = 0;
        for(char c: cur_s)
            if(c == '#')
                res ++;
        return res;
    }

private:
    string change(const string& s){

        vector<string> grid = s_to_grid(s);
        int sz = grid.size();

        int new_sz, step;
        if(sz % 2 == 0){
            new_sz = sz / 2 * 3;
            step = 2;
        }
        else{
            assert(sz % 3 == 0);
            new_sz = sz / 3 * 4;
            step = 3;
        }
        string empty = "";
        for(int i = 0 ; i < new_sz ; i ++)
            empty += " ";
        vector<string> new_grid(new_sz, empty);

        for(int i = 0 ; i < grid.size() ; i += step)
            for(int j = 0 ; j < grid[i].size() ; j += step){
                vector<string> part = get_part_grid(grid, i, j, step);
                string part_s = grid_to_s(part);
                assert(rules.find(part_s) != rules.end());
                string changed_s = rules[part_s];
                vector<string> changed_part = s_to_grid(changed_s);
                put_grid(new_grid, changed_part, i / step * (step + 1), j / step * (step + 1));

                // print_grid(new_grid);
            }

        return grid_to_s(new_grid);
    }

    void put_grid(vector<string>& grid, const vector<string>& part, int x, int y){

        for(int i = 0 ; i < part.size() ; i ++)
            for(int j = 0 ; j < part[i].size() ; j ++)
                grid[x + i][y + j] = part[i][j];
    }
    vector<string> get_part_grid(const vector<string>& grid, int x, int y, int step){

        vector<string> res;
        for(int i = x ; i < x + step ; i ++)
            res.push_back(grid[i].substr(y, step));
        return res;
    }

    void get_rules(const vector<string>& raw_rules){

        for(const string& raw_rule: raw_rules){
            stringstream ss(raw_rule);
            string a, b;

            ss >> a;
            ss >> b;
            ss >> b;
            // cout << a << " " << b << endl;

            for(int i = 0; i < 4; i ++){
                rules[a] = b;
                a = rotate(a);
            }
            a = flip(a);
            for(int i = 0; i < 4; i ++){
                rules[a] = b;
                a = rotate(a);
            }
        }
    }

    string rotate(const string& s){
        vector<string> grid = s_to_grid(s);
        // print_grid(grid);

        int sz = grid.size();
        string empty_str = "";
        for(int i = 0 ; i < sz ; i ++)
            empty_str += " ";
        vector<string> res(sz, empty_str);

        // rotate
        for(int i = 0 ; i < sz ; i ++)
            for(int j = 0 ; j < sz ; j ++)
                res[j][sz-1-i] = grid[i][j];

        return grid_to_s(res);
    }

    string flip(const string& s){
        vector<string> grid = s_to_grid(s);

        int sz = grid.size();
        string empty_str = "";
        for(int i = 0 ; i < sz ; i ++)
            empty_str += " ";
        vector<string> res(sz, empty_str);

        // flip
        for(int i = 0 ; i < sz ; i ++)
            for(int j = 0 ; j < sz ; j ++)
                res[i][j] = grid[sz - 1 - i][j];

        return grid_to_s(res);
    }

    vector<string> s_to_grid(const string& s){

        string line = s;
        int sz = line.find('/');
        assert(sz != string::npos);
        // cout << sz << endl;

        vector<string> res;
        for(int i = 0 ; i < sz; i ++){
            // cout << i << ":" << line.substr(0, sz) << endl;
            assert(line.substr(0, sz).size() == sz);
            res.push_back(line.substr(0, sz));

            if(sz + 1 < line.size())
                line = line.substr(sz + 1);
            else
                assert(line.size() == sz && res.size() == sz);
        }
        // print_grid(res);
        return res;
    }

    string grid_to_s(const vector<string>& grid){
        string res = "";
        for(const string& row: grid){
            res += row;
            res += "/";
        }
        assert(res.size() == (grid.size() + 1) * grid.size());
        return res.substr(0, res.size() - 1);
    }

    void print_grid(const vector<string>& grid){
        for(const string& row: grid)
            cout << row << endl;
        cout << endl;
    }

    void print_rules(){
        for(const pair<string, string>& p: rules)
            cout << p.first << " => " << p.second << endl;
    }
};

int main() {

    vector<string> raw_rules_test = {
            "../.# => ##./#../...",
            ".#./..#/### => #..#/..../..../#..#"
    };
    cout << Solution().pixel_num(2, raw_rules_test) << endl;

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<string> raw_rules;
    string line;
    while(!input.eof()) {
        getline(input, line);
        raw_rules.push_back(line);
    }

    cout << Solution().pixel_num(5, raw_rules) << endl;

    input.close();

    return 0;
}