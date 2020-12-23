/// Source : https://adventofcode.com/2020/day/19
/// Author : liuyubobobo
/// Time   : 2020-12-22

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

using namespace std;


class Solution{

public:
    unordered_set<string> solve(const unordered_map<int, string>& rules){

        return dfs(rules, 0);
    }

private:
    unordered_set<string> dfs(const unordered_map<int, string>& rules, int index){

        string s = rules.at(index);
        int qindex = s.find('\"');
        unordered_set<string> ret;
        if(qindex != string::npos){
            int end = s.find('\"', qindex + 1);
            ret = {s.substr(qindex + 1, end - (qindex + 1))};
            return ret;
        }

        vector<vector<int>> rule;
        while(true){
            int barindex = s.find('|');
            if(barindex == string::npos){
                rule.push_back(get_rule(s));
                break;
            }

            rule.push_back(get_rule(s.substr(0, barindex)));
            s = s.substr(barindex + 1);
        }

        for(const vector<int>& r: rule){
            if(r.size() > 2){
                for(int e: r) cout << e << " "; cout << endl;
                assert(false);
            }
            for(const string& s1: dfs(rules, r[0])){
                if(r.size() == 1) ret.insert(s1);
                else{
                    for(const string& s2: dfs(rules, r[1]))
                        ret.insert(s1 + s2);
                }
            }
        }

        return ret;
    }

    vector<int> get_rule(const string& s){

        vector<int> res;
        for(int start = next_digit(s, 0), i = start + 1; i <= s.size(); i ++)
            if(i == s.size() || !isdigit(s[i])){
                res.push_back(atoi(s.substr(start, i - start).c_str()));
                start = next_digit(s, i);
                i = start;
            }
        return res;
    }

    int next_digit(const string& s, int start){
        for(int i = start; i < s.size(); i ++)
            if(isdigit(s[i])) return i;
        return s.size();
    }
};

int main() {

    ifstream input;
    input.open("../../input1.txt");
    assert(input.is_open());

    string line;
    unordered_map<int, string> rules;
    while(true){
        getline(input, line);
        if(line == "") break;

        int cindex = line.find(':');
        assert(cindex != string::npos);
        rules[atoi(line.substr(0, cindex).c_str())] = line.substr(cindex + 2);
    }

    unordered_set<string> set = Solution().solve(rules);
    int res = 0;
    while(!input.eof()){
        input >> line;
        res += set.count(line);
    }
    cout << res << endl;

    input.close();

    return 0;
}
