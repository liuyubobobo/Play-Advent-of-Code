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

        unordered_set<char> set;
        for(char c: s)
            set.insert(c);
        return set.size();
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test.txt");
    assert(input.is_open());

    string line;
    string data = "";
    int res = 0;
    while(!input.eof()){
        getline(input, line);
        if(line == ""){
            res += Solution().solve(data);
            data = "";
        }
        else data += line;
    }
    res += Solution().solve(data);

    cout << res << endl;

    input.close();

    return 0;
}
