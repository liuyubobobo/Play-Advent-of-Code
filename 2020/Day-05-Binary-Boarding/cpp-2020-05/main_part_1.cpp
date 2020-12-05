/// Source : https://adventofcode.com/2020/day/5
/// Author : liuyubobobo
/// Time   : 2020-12-05

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_set>

using namespace std;


class Solution{

public:
    int solve(const string& s){

        int rowl = 0, rowr = 127;
        for(int i = 0; i < 7; i ++){
            int mid = (rowl + rowr) / 2;
            if(s[i] == 'B') rowl = mid + 1;
            else rowr = mid;
        }
        assert(rowl == rowr);

        int coll = 0, colr = 7;
        for(int i = 7; i < 10; i ++){
            int mid = (coll + colr) / 2;
            if(s[i] == 'R') coll = mid + 1;
            else colr = mid;
        }
        assert(coll == colr);

        return rowl * 8 + coll;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string line;
    int res = 0;
    while(!input.eof()){
        input >> line;
        res = max(res, Solution().solve(line));
    }

    cout << res << endl;

    input.close();

    return 0;
}
