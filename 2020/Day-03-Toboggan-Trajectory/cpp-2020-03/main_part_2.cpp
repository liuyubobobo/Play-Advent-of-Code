/// Source : https://adventofcode.com/2020/day/3#part2
/// Author : liuyubobobo
/// Time   : 2020-12-03

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;


class Solution{

public:
    long long solve(const vector<string>& g){

        int a = solve(g, 1, 1);
        int b = solve(g, 1, 3);
        int c = solve(g, 1, 5);
        int d = solve(g, 1, 7);
        int e = solve(g, 2, 1);
        return (long long)a * b * c * d * e;
    }

    int solve(const vector<string>& g, int down, int right){

        int R = g.size(), C = g[0].size();
        int res = 0, x = 0, y = 0;
        while(x < R){
            res += (g[x][y] == '#');
            x += down;
            y = (y + right) % C;
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
