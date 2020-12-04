/// Source : https://adventofcode.com/2020/day/3
/// Author : liuyubobobo
/// Time   : 2020-12-03

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;


class Solution{

public:
    int solve(const vector<string>& g){

        int R = g.size(), C = g[0].size();
        int res = 0, x = 0, y = 0;
        while(x < R){
            res += (g[x][y] == '#');
            x ++;
            y = (y + 3) % C;
        }
        return res;
    }
};

int main() {

    ifstream input;
//    input.open("../../test_input.txt");
    input.open("../../input.txt");
    assert(input.is_open());

    vector<string> g;
    string line;
    while(!input.eof()){
        input >> line;
        g.push_back(line);
    }

//    for(const string& line: g) cout << line << endl;
    cout << Solution().solve(g) << endl;

    input.close();

    return 0;
}
