/// Source : https://adventofcode.com/2020/day/17
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
    int R, C, H;

public:
    int solve(const vector<string>& g){

        int r = g.size(), c = g[0].size();

        R = r + 14, C = c + 14, H = 1 + 14;
        vector<vector<string>> space(R, vector<string>(C, string(H, '.')));

        for(int i = 0; i < r; i ++)
            for(int j = 0; j < c; j ++)
                space[i + 7][j + 7][7] = g[i][j];

        for(int k = 0; k < 6; k ++){
            vector<vector<string>> space2 = get_space(space);
            space = space2;
        }

        int res = 0;
        for(int i = 0; i < space.size(); i ++)
            for(int j = 0; j < space[i].size(); j ++)
                for(char c: space[i][j])
                    res += c == '#';
        return res;
    }

private:
    vector<vector<string>> get_space(const vector<vector<string>>& space){

        vector<vector<string>> res(R, vector<string>(C, string(H, '.')));
        for(int i = 0; i < R; i ++)
            for(int j = 0; j < C; j ++)
                for(int k = 0; k < H; k ++){
                    int active_num = get_active_num(space, i, j, k);
                    if(space[i][j][k] == '#'){
                        if(active_num == 2 || active_num == 3) res[i][j][k] = '#';
                    }
                    else{
                        if(active_num == 3) res[i][j][k] = '#';
                    }
                }
        return res;
    }

    int get_active_num(const vector<vector<string>>& space, int i, int j, int k){

        int res = 0;
        for(int a = i - 1; a <= i + 1; a ++)
            for(int b = j - 1; b <= j + 1; b ++)
                for(int c = k - 1; c <= k + 1; c ++){
                    if(a == i && b == j && c == k) continue;
                    res += in_area(a, b, c) && space[a][b][c] == '#';
                }
        return res;
    }

    bool in_area(int a, int b, int c){
        return 0 <= a && a < R && 0 <= b && b < C && 0 <= c && c < H;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 112
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
