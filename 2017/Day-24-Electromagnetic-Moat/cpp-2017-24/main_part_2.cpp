/// http://adventofcode.com/2017/day/24
/// liuyubobobo
/// 2018-03-09

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <sstream>

using namespace std;


class Solution{

private:
    unordered_map<int, vector<pair<int, int>>> g;
    set<pair<int, int>> used;

public:
    int longest_strongest(const vector<string>& g_str){

        create_g(g_str);
        used.clear();
        pair<int, int> res = dfs(0);
        return res.second;
    }

private:
    pair<int, int> dfs(int index){

        pair<int, int> res = make_pair(0, 0);
        for(const pair<int, int>& edge: g[index])
            if(used.find(make_pair(index, edge.first)) == used.end() &&
                         used.find(make_pair(edge.first, index)) == used.end()){
                used.insert(make_pair(index, edge.first));
                used.insert(make_pair(edge.first, index));
                pair<int, int> t_res = dfs(edge.first);
                t_res.first += 1;
                t_res.second += edge.second;
                res = max(res, t_res);
                used.erase(make_pair(index, edge.first));
                used.erase(make_pair(edge.first, index));
            }

        return res;
    }

    void create_g(const vector<string>& g_str){

        g.clear();
        for(const string& line: g_str){
            stringstream ss(line);

            int a, b;
            char c;
            ss >> a >> c >> b;
            // cout << a << c << b << endl;
            g[a].push_back(make_pair(b, a+b));
            g[b].push_back(make_pair(a, a+b));
        }
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<string> g_str;
    string line;
    while(!input.eof()) {
        getline(input, line);
        g_str.push_back(line);
    }

    cout << Solution().longest_strongest(g_str) << endl;

    input.close();

    return 0;
}