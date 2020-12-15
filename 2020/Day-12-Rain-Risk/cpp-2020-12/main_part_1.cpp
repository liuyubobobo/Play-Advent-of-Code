/// Source : https://adventofcode.com/2020/day/12
/// Author : liuyubobobo
/// Time   : 2020-12-12

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_set>

using namespace std;


class Solution{

private:
    const int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

public:
    int solve(vector<string>& ins){

        int x = 0, y = 0, d = 0;
        for(const string& s: ins){
            char c = s[0];
            int k = atoi(s.substr(1).c_str());

            switch (c) {
                case 'N': x -= k; break;
                case 'S': x += k; break;
                case 'E': y += k; break;
                case 'W': y -= k; break;
                case 'F': x += dirs[d][0] * k; y += dirs[d][1] * k; break;
                case 'R':
                    for(int i = 0; i < k / 90; i ++)
                        d = (d + 1) % 4;
                    break;
                case 'L':
                    for(int i = 0; i < k / 90; i ++)
                        d = (d + 3) % 4;
                    break;
                default:assert(false);
            }
        }
        return abs(x) + abs(y);
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 25
    assert(input.is_open());

    string line;
    vector<string> ins;
    while(!input.eof()){
        input >> line;
        ins.push_back(line);
    }

    cout << Solution().solve(ins) << endl;

    input.close();

    return 0;
}
