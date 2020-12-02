/// Source : https://adventofcode.com/2015/day/2#part2
/// Author : liuyubobobo
/// Time   : 2020-12-02

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;


class Solution{

public:
    int solve(const vector<int>& v){

        return 2 * (v[0] + v[1] + v[2] - max(v[0], max(v[1], v[2]))) +
               v[0] * v[1] * v[2];
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string s;
    int res = 0;
    while(!input.eof()) {

        input >> s;

        vector<int> v;
        for (int start = 0, i = start + 1; i <= s.size(); i++)
            if (i == s.size() || s[i] == 'x') {
                v.push_back(atoi(s.substr(start, i - start).c_str()));
                start = i + 1;
                i = start;
            }
        assert(v.size() == 3);
        res += Solution().solve(v);
    }

    cout << res << endl;
    input.close();

    return 0;
}
