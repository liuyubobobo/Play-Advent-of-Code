/// Source : https://adventofcode.com/2020/day/11#part2
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
    const int dirs[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1},
                            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int R, C;

public:
    int solve(vector<string>& g){

        R = g.size(), C = g[0].size();
        while(true){
            vector<string> g2 = change(g);
            if(g == g2) break;
            g = g2;
        }

        int res = 0;
        for(const string& row: g)
            for(char c: row) res += c == '#';
        return res;
    }

private:
    vector<string> change(const vector<string>& g){

        vector<string> res = g;
        for(int i = 0; i < R; i ++)
            for(int j = 0; j < C; j ++){
                if(g[i][j] == 'L' && occupied(g, i, j) == 0)
                    res[i][j] = '#';
                else if(g[i][j] == '#' && occupied(g, i, j) >= 5)
                    res[i][j] = 'L';
            }
        return res;
    }

    int occupied(const vector<string>& g, int x, int y){

        int res = 0;
        for(int d = 0; d < 8; d ++){
            for(int k = 1;;k ++){
                int nx = x + k * dirs[d][0], ny = y + k * dirs[d][1];
                if(!in_area(nx, ny)) break;

                if(g[nx][ny] == '#'){
                    res ++;
                    break;
                }
                else if(g[nx][ny] == 'L') break;
            }
        }
        return res;
    }

    bool in_area(int x, int y){
        return x >= 0 && x < R && y >= 0 && y < C;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 35
//    input.open("../../input_test_2.txt"); // 220
    assert(input.is_open());

    string line;
    vector<string> g;
    while(!input.eof()){
        input >> line;
        g.push_back(line);
    }

    cout << Solution().solve(g) << endl;

    input.close();

    return 0;
}
