/// Source : https://adventofcode.com/2020/day/8
/// Author : liuyubobobo
/// Time   : 2020-12-07

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_set>

using namespace std;


class Solution{

public:
    int solve(const vector<pair<string, int>>& lines){

        int var = 0, cur = 0;
        unordered_set<int> set;
        while(!set.count(cur)){
            set.insert(cur);

            if(lines[cur].first == "acc"){
                var += lines[cur].second;
                cur ++;
            }
            else if(lines[cur].first == "jmp"){
                cur += lines[cur].second;
            }
            else if(lines[cur].first == "nop") cur ++;
        }
        return var;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string code;
    int offset;
    vector<pair<string, int>> lines;
    while(!input.eof()){
        input >> code >> offset;
        lines.push_back({code, offset});
    }

    cout << Solution().solve(lines) << endl;

    input.close();

    return 0;
}
