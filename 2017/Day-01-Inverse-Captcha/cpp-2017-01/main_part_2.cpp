/// http://adventofcode.com/2017/day/1
/// liuyubobobo
/// 2018-02-22

#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

class Solution{

public:
    int sum(const string& s){

        int step = s.size() / 2;

        int res = 0;
        for(int i = 0 ; i < s.size() ; i ++)
            if(s[i] == s[(i + step) % s.size()])
                res += (s[i] - '0');
        return res;
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string s;
    input >> s;
    cout << Solution().sum(s) << endl;

    input.close();

    return 0;
}