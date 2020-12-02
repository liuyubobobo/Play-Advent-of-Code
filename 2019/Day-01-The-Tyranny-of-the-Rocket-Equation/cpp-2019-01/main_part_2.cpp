/// Source : https://adventofcode.com/2019/day/1#part2
/// Author : liuyubobobo
/// Time   : 2020-12-02

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;


class Solution{

public:
    int solve(int x){

        int res = 0;
        while(true){
            int t = x / 3 - 2;
            if(t > 0) res += t, x = t;
            else break;
        }
        return res;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    int x, res = 0;
    while(!input.eof()){
        input >> x;
        res += Solution().solve(x);
    }
    cout << res << endl;

    input.close();

    return 0;
}
