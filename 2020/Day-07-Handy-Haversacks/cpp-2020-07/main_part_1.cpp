/// Source : https://adventofcode.com/2020/day/7
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

        unordered_map<string, unordered_set<string>> g;
        getG(rules, g);

        queue<string> q;
        q.push("shiny gold bag");
        unordered_set<string> visited;
        visited.insert("shiny gold bag");
        int res = 0;
        while(!q.empty()){
            string cur = q.front();
            q.pop();

            res ++;
            for(const string& next: g[cur])
                if(!visited.count(next)){
                    q.push(next);
                    visited.insert(next);
                }
        }
        return res - 1;
    }

private:
    void getG(const vector<string>& rules,
              unordered_map<string, unordered_set<string>>& g){

        for(const string& rule: rules){
            vector<string> bags = get_bags(rule);
            for(int i = 1; i < bags.size(); i ++)
                g[bags[i]].insert(bags[0]);
        }
    }

    vector<string> get_bags(const string& s){

        int contain_index = s.find("contain");
        assert(contain_index != string::npos);

        vector<string> res = {s.substr(0, contain_index - 2)};
        assert(res[0].substr(res[0].size() - 3) == "bag");

        string left = s.substr(contain_index + 8);
        assert(isdigit(left[0]) || left.substr(0, 2) == "no");
        if(!isdigit(left[0])) return res;

        for(int start = 0, i = start + 1; i < left.size(); i ++)
            if(left[i] == ',' || left[i] == '.'){
                string bag = left.substr(start, i - start);
                if(bag.back() == 's') bag.pop_back();

                int space_index = bag.find(' ');
                res.push_back(bag.substr(space_index + 1));

                start = i + 2;
                if(start < left.size() && !isdigit(left[start]))
                    assert(false);

                i = start;
            }
        return res;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test.txt");
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
