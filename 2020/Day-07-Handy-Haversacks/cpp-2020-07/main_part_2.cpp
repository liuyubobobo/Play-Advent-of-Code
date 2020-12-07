/// Source : https://adventofcode.com/2020/day/7#part2
/// Author : liuyubobobo
/// Time   : 2020-12-07

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>

using namespace std;


class Solution{

public:
    int solve(const vector<string>& rules){

        unordered_map<string, unordered_map<string, int>> g;
        for(const string& rule: rules)
            get_bags(g, rule);

        assert(g.count("shiny gold bag"));
        unordered_map<string, int> dp;
        return dfs(g, "shiny gold bag", dp) - 1;
    }

private:
    int dfs(const unordered_map<string, unordered_map<string, int>>& g,
            string v, unordered_map<string, int>& dp){

        if(dp.count(v)) return dp[v];

        int res = 1;
        for(const pair<string, int>& p: g.at(v))
            res += p.second * dfs(g, p.first, dp);
        return dp[v] = res;
    }

    void get_bags(unordered_map<string, unordered_map<string, int>>& g,
                  const string& s){

        int contain_index = s.find("contain");
        assert(contain_index != string::npos);

        string p = s.substr(0, contain_index - 2);
        assert(p.substr(p.size() - 3) == "bag");

        string left = s.substr(contain_index + 8);
        assert(isdigit(left[0]) || left.substr(0, 2) == "no");
        if(!isdigit(left[0])){
            g[p];
            return;
        }

        for(int start = 0, i = start + 1; i < left.size(); i ++)
            if(left[i] == ',' || left[i] == '.'){
                string bag_s = left.substr(start, i - start);
                if(bag_s.back() == 's') bag_s.pop_back();

                int space_index = bag_s.find(' ');
                int num = atoi(bag_s.substr(0, space_index).c_str());
                string bag = bag_s.substr(space_index + 1);
                g[p][bag] = num;

                start = i + 2;
                if(start < left.size() && !isdigit(left[start]))
                    assert(false);

                i = start;
            }
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 32
    assert(input.is_open());

    string line;
    vector<string> rules;
    while(!input.eof()){
        getline(input, line);
        rules.push_back(line);
    }

    cout << Solution().solve(rules) << endl;

    input.close();

    return 0;
}
