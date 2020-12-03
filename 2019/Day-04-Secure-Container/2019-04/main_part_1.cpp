/// Source : https://adventofcode.com/2019/day/4
/// Author : liuyubobobo
/// Time   : 2020-12-03

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <set>
#include <unordered_map>

using namespace std;


class Solution{

public:
    int solve(int a, int b){

        int res = 0;
        for(int i = a; i <= b; i ++)
            res += ok(i);
        return res;
    }

private:
    bool ok(int x){

        string s = to_string(x);
        bool same = false;
        for(int i = 1; i < s.size(); i ++){
            if(s[i - 1] > s[i]) return false;
            if(s[i - 1] == s[i]) same = true;
        }

        return same;
    }
};

int main() {

    cout << Solution().solve(240920, 789857) << endl;

    return 0;
}
