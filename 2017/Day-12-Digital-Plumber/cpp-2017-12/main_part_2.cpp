/// http://adventofcode.com/2017/day/12
/// liuyubobobo
/// 2018-02-23

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;


class Solution{

private:
    unordered_map<int, vector<int>> g;
    unordered_set<int> visited;

public:
    int groups_num(const vector<string>& lines){

        g.clear();
        create_g(lines);

        visited.clear();
        int res = 0;
        for(auto& p: g)
            if(visited.find(p.first) == visited.end()){
                res ++;
                dfs(p.first);
            }

        return res;
    }

private:
    void dfs(int node_id){

        visited.insert(node_id);
        for(int next: g[node_id])
            if(visited.find(next) == visited.end())
                dfs(next);
        return;
    }

    void create_g(const vector<string>& lines){

        for(const string& line: lines){
            stringstream ss(line);

            int v;
            ss >> v;

            string s;
            ss >> s;

            int w;
            while(ss >> s){
                if(s[s.size()-1] == ',')
                    s = s.substr(0, s.size()-1);
                w = stoi(s);
                g[v].push_back(w);
                if(w != v)
                    g[w].push_back(v);
            }
        }
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<string> lines;
    string line;
    while(!input.eof()){
        getline(input, line);
        lines.push_back(line);
    }

    cout << Solution().groups_num(lines) << endl;

    input.close();

    return 0;
}