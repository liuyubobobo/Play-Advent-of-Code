/// Source : https://adventofcode.com/2015/day/3
/// Author : liuyubobobo
/// Time   : 2020-12-03

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <set>

using namespace std;


class Solution{

public:
    int solve(const string& s){

        unordered_map<char, int> dx = {{'^', 0}, {'v', 0}, {'>', 1}, {'<', -1}};
        unordered_map<char, int> dy = {{'^', 1}, {'v', -1}, {'>', 0}, {'<', 0}};

        set<pair<int, int>> set;
        int x = 0, y = 0;
        set.insert({x, y});
        for(char c: s){
            x += dx[c], y += dy[c];
            set.insert({x, y});
        }
        return set.size();
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string s;
    input >> s;
    cout << Solution().solve(s) << endl;
    input.close();

    return 0;
}
