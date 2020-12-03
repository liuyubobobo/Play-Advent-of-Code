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
        bool ok = false;
        for(int i = 1; i < s.size(); i ++){
            if(s[i - 1] > s[i]) return false;
            if(s[i - 1] == s[i]){
                if(i - 2 >= 0 && s[i - 2] == s[i]) continue;
                if(i + 1 < s.size() && s[i + 1] == s[i]) continue;
                ok = true;
            }
        }
        return ok;
    }
};

int main() {

    cout << Solution().solve(240920, 789857) << endl;

    return 0;
}
