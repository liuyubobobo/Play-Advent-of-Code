/// Source : https://adventofcode.com/2020/day/21
/// Author : liuyubobobo
/// Time   : 2020-12-24

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

using namespace std;


class Solution{

public:
    int solve(const vector<pair<vector<string>, vector<string>>>& data){

        unordered_map<string, unordered_set<string>> table;
        for(const pair<vector<string>, vector<string>>& p: data){
            const vector<string> &food = p.first, &allergen = p.second;
            for(const string& allerg: allergen)
                if(!table.count(allerg))
                    table[allerg] = unordered_set<string>(food.begin(), food.end());
                else
                    table[allerg] = i(table[allerg], unordered_set<string>(food.begin(), food.end()));
        }

        unordered_set<string> possible;
        for(const pair<string, unordered_set<string>>& p: table){
//            cout << p.second.size() << endl;
            for(const string& s: p.second) possible.insert(s);
        }
        cout << "possible : ";
        for(const string& s: possible) cout << s << " "; cout << endl;

        int res = 0;
        for(const pair<vector<string>, vector<string>>& p: data)
            for(const string& s: p.first)
                if(!possible.count(s)) res ++;
        return res;
    }

private:
    unordered_set<string> i(const unordered_set<string>& a, const unordered_set<string>& b){
        unordered_set<string> res;
        for(const string& s: a)
            if(b.count(s)) res.insert(s);
        return res;
    }
};

int next_ch(const string& s, int start){

    for(int i = start; i < s.size(); i ++)
        if(isalpha(s[i])) return i;
    return s.size();
}

vector<string> get(const string& s){

    vector<string> ret;
    for(int start = next_ch(s, 0), i = start + 1; i <= s.size(); i ++)
        if(i == s.size() || !isalpha(s[i])){
            ret.push_back(s.substr(start, i - start));
            start = next_ch(s, i);
            i = start;
        }
    return ret;
}

int main() {

    ifstream input;
//    input.open("../../input_test_1.txt"); // 5
    input.open("../../input.txt");
    assert(input.is_open());

    string line;
    vector<pair<vector<string>, vector<string>>> data;
    while(!input.eof()){
        getline(input, line);

        int lindex = line.find('(');
        vector<string> a = get(line.substr(0, lindex - 1));
        vector<string> b = get(line.substr(lindex + 10, line.size() - 1 - (lindex + 10)));
        data.push_back({a, b});

//        for(const string& s: a) cout << s << " "; cout << endl;
//        for(const string& s: b) cout << s << " "; cout << endl;
    }
    cout << Solution().solve(data) << endl;

    input.close();

    return 0;
}
