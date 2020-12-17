/// Source : https://adventofcode.com/2020/day/17#part2
/// Author : liuyubobobo
/// Time   : 2020-12-17

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;


class Solution{

private:
    int R, C, H, W;

public:
    int solve(const vector<string>& g){

        int r = g.size(), c = g[0].size();

        R = r + 14, C = c + 14, H = 1 + 14, W = 1 + 14;
        vector<vector<vector<string>>> space(R, vector<vector<string>>(C, vector<string>(H, string(W, '.'))));

        for(int i = 0; i < r; i ++)
            for(int j = 0; j < c; j ++)
                space[i + 7][j + 7][7][7] = g[i][j];

        for(int k = 0; k < 6; k ++){
            vector<vector<vector<string>>> space2 = get_space(space);
            space = space2;
        }

        int res = 0;
        for(int i = 0; i < space.size(); i ++)
            for(int j = 0; j < space[i].size(); j ++)
                for(int k = 0; k < space[i][j].size(); k ++)
                    for(char c: space[i][j][k])
                        res += c == '#';
        return res;
    }

private:
    vector<vector<vector<string>>> get_space(const vector<vector<vector<string>>>& space){

        vector<vector<vector<string>>> res(R, vector<vector<string>>(C, vector<string>(H, string(W, '.'))));
        for(int i = 0; i < R; i ++)
            for(int j = 0; j < C; j ++)
                for(int k = 0; k < H; k ++)
                    for(int l = 0; l < W; l ++){
                        int active_num = get_active_num(space, i, j, k, l);
                        if(space[i][j][k][l] == '#'){
                            if(active_num == 2 || active_num == 3) res[i][j][k][l] = '#';
                        }
                        else{
                            if(active_num == 3) res[i][j][k][l] = '#';
                        }
                 }
        return res;
    }

    int get_active_num(const vector<vector<vector<string>>>& space, int i, int j, int k, int l){

        int res = 0;
        for(int a = i - 1; a <= i + 1; a ++)
            for(int b = j - 1; b <= j + 1; b ++)
                for(int c = k - 1; c <= k + 1; c ++)
                    for(int d = l - 1; d <= l + 1; d ++){
                        if(a == i && b == j && c == k && d == l) continue;
                        res += in_area(a, b, c, d) && space[a][b][c][d] == '#';
                    }
        return res;
    }

    bool in_area(int a, int b, int c, int d){
        return 0 <= a && a < R && 0 <= b && b < C && 0 <= c && c < H && 0 <= d && d < W;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 848
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
