/// Source : https://adventofcode.com/2015/day/5#part2
/// Author : liuyubobobo
/// Time   : 2020-12-03

#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_set>

using namespace std;


class Solution{

public:
    bool is_nice(const string& s){

        bool between = false;
        for(int i = 1; i + 1 < s.size(); i ++)
            if(s[i - 1] == s[i + 1]){
                between = true;
                break;
            }
        if(!between) return false;

        for(int i = 1; i < s.size(); i ++){
            string t = s.substr(i - 1, 2);
            if(s.find(t, i + 1) != string::npos) return true;
        }
        return false;

    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string s;
    int res = 0;
    while(!input.eof()){
        input >> s;
        res += Solution().is_nice(s);
    }
    cout << res << endl;
    input.close();

    return 0;
}
