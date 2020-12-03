/// Source : https://adventofcode.com/2015/day/3#part2
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
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        set.insert({0, 0});
        for(int i = 0; i < s.size(); i ++){
            if(i % 2 == 0){
                x1 += dx[s[i]], y1 += dy[s[i]];
                set.insert({x1, y1});
            }
            else{
                x2 += dx[s[i]], y2 += dy[s[i]];
                set.insert({x2, y2});
            }
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
