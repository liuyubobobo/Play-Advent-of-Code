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
    int contain0(const vector<string>& lines){

        g.clear();
        create_g(lines);

        visited.clear();
        return dfs(0);
    }

private:
    int dfs(int node_id){
        int res = 1;
        visited.insert(node_id);
        for(int next: g[node_id])
            if(visited.find(next) == visited.end())
                res += dfs(next);
        return res;
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

    cout << Solution().contain0(lines) << endl;

    input.close();

    return 0;
}