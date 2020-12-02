/// Source : https://adventofcode.com/2019/day/2
/// Author : liuyubobobo
/// Time   : 2020-12-02

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;


class Solution{

public:
    int solve(vector<int>& code){

        code[1] = 12, code[2] = 2;

        int cur = 0;
        while(code[cur] != 99){
            int a = code[code[cur + 1]];
            int b = code[code[cur + 2]];
            code[code[cur + 3]] = code[cur] == 1 ? a + b : a * b;
            cur += 4;
        }
        return code[0];
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string s;
    input >> s;

    vector<int> code;
    for(int start = 0, index = start + 1; index <= s.size(); index ++)
        if(index == s.size() || s[index] == ','){
            code.push_back(atoi(s.substr(start, index - start).c_str()));
            start = index + 1;
            index = start;
        }

    cout << Solution().solve(code) << endl;

    input.close();

    return 0;
}
