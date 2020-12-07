/// Source : https://adventofcode.com/2020/day/6#part2
/// Author : liuyubobobo
/// Time   : 2020-12-05

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;


class Solution{

public:
    int solve(const vector<string>& group){

        unordered_map<char, int> f;
        for(const string& s: group)
            for(char c: s) f[c] ++;

        int res = 0;
        for(const pair<char, int>& p: f)
            if(p.second == group.size()) res ++;
        return res;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test.txt");
    assert(input.is_open());

    string line;
    vector<string> group;
    int res = 0;
    while(!input.eof()){
        getline(input, line);
        if(line == ""){
            res += Solution().solve(group);
            group.clear();
        }
        else group.push_back(line);
    }
    res += Solution().solve(group);

    cout << res << endl;

    input.close();

    return 0;
}
