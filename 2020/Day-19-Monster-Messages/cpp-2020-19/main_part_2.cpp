/// Source : https://adventofcode.com/2020/day/19#part2
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

private:
    unordered_set<string> set42, set31;

public:
    Solution(const unordered_map<int, string>& rules){

        set42 = dfs(rules, 42);
        assert(set42.size() > 0);
        int len = set42.begin()->size();

        cout << "set42 : size = " << set42.size() << endl;
        for(const string& s: set42){
//            cout << s << endl;
            assert(s.size() == len);
        }
//        cout << endl;

        set31 = dfs(rules, 31);
        cout << "set31 : size = " << set31.size() << endl;
        for(const string& s: set31){
//            cout << s << endl;
            assert(s.size() == len);
        }
//        cout << endl;

        for(const string& s1: set42)
            for(const string& s2: set31)
                assert(s1 != s2);

        for(int k = 0; k < 100000; k ++){
            string s = "";
            for(int i = 0; i < len; i ++)
                s += (rand() % 2 ? 'a' : 'b');
            assert(set42.count(s) || set31.count(s));
        }
    }

    bool is_ok(const string& s){

        if(s.size() % 8) return false;

        vector<int> pattern;
        for(int i = 0; i < s.size(); i += 8)
            if(set42.count(s.substr(i, 8))) pattern.push_back(0);
            else if(set31.count(s.substr(i, 8))) pattern.push_back(1);
            else{
                cout << s.substr(i, 8) << endl;
                assert(false);
            }

        int zero = 0, one = 0, k = -1;
        for(int i = 0; i < pattern.size(); i ++)
            if(pattern[i] == 0){
                zero ++;
                continue;
            }
            else{
                k = i;
                break;
            }

        if(k <= 0)
            return false;

        for(int i = k; i < pattern.size(); i ++)
            if(pattern[i] == 1){
                one ++;
                continue;
            }
            else return false;

        assert(zero + one == pattern.size());
        return zero > one;
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
    input.open("../../input.txt");
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

    Solution solution(rules);
    int res = 0;
    while(!input.eof()){
        input >> line;
        res += solution.is_ok(line);
    }
    cout << res << endl;

    input.close();

    return 0;
}
