/// Source : https://adventofcode.com/2020/day/12#part2
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

        int x = 0, y = 0, d = 0, wx = -1, wy = 10;
        cout << "ship : " << x << " " << y << " waypoint : " << wx << " " << wy << endl;
        for(const string& s: ins){
            char c = s[0];
            int k = atoi(s.substr(1).c_str());

            switch (c) {
                case 'N': wx -= k; break;
                case 'S': wx += k; break;
                case 'E': wy += k; break;
                case 'W': wy -= k; break;
                case 'F': x += wx * k; y += wy * k; break;
                case 'R':
                    for(int i = 0; i < k / 90; i ++){
                        swap(wx, wy);
                        wy *= -1;
                    }
                    break;
                case 'L':
                    for(int i = 0; i < k / 90; i ++){
                        swap(wx, wy);
                        wx *= -1;
                    }
                    break;
                default:assert(false);
            }
//            cout << "ship : " << x << " " << y << " waypoint : " << wx << " " << wy << endl;
        }
        return abs(x) + abs(y);
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 286
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
