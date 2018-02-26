/// http://adventofcode.com/2017/day/19
/// liuyubobobo
/// 2018-02-25

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>

using namespace std;


class Solution{

private:
    int N, M;
    int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
public:
    string path(const vector<string>& g){

        N = g.size();
        assert(g.size() > 0);
        M = g[0].size();

        string res = "";
        int start_x = 0;
        int start_y = get_start_y(g[0]);

        int cur_x = start_x, cur_y = start_y;
        int cur_d = 0;
        while(true){
            int next_x = cur_x + d[cur_d][0];
            int next_y = cur_y + d[cur_d][1];
            if(!in_area(next_x, next_y) || is_end(g[next_x][next_y]))
                break;

            if(isalpha(g[next_x][next_y]))
                res += g[next_x][next_y];
            else if(g[next_x][next_y] == '+'){
                if(cur_d <= 1){
                    assert(cur_d == 0 || cur_d == 1);
                    for(int next_d = 2; next_d < 4 ; next_d ++){
                        int new_x = next_x + d[next_d][0];
                        int new_y = next_y + d[next_d][1];
                        if(in_area(new_x, new_y) && (isalpha(g[new_x][new_y]) || g[new_x][new_y] == '-')){
                            cur_d = next_d;
                            break;
                        }
                    }
                }
                else{
                    assert(cur_d == 2 || cur_d == 3);
                    for(int next_d = 0; next_d < 2 ; next_d ++){
                        int new_x = next_x + d[next_d][0];
                        int new_y = next_y + d[next_d][1];
                        if(in_area(new_x, new_y) && (isalpha(g[new_x][new_y]) || g[new_x][new_y] == '|')){
                            cur_d = next_d;
                            break;
                        }
                    }
                }
            }
            else
                assert(g[next_x][next_y] == '-' || g[next_x][next_y] == '|');

            cur_x = next_x, cur_y = next_y;
        }

        return res;
    }

private:
    int get_start_y(const string& s){
        for(int i = 0 ; i < s.size() ; i ++)
            if(s[i] != ' '){
                assert(s[i] == '|');
                return i;
            }
        assert(false);
        return -1;
    }

    bool in_area(int x, int y){
        return x >= 0 && x < N && y >= 0 && y < M;
    }

    bool is_end(char x){
        return x != '|' && x != '-' && x != '+' && !isalpha(x);
    }
};

int main() {

    vector<string> g_test = {
            "    |         ",
            "    |  +--+   ",
            "    A  |  C   ",
            "F---|----E|--+",
            "    |  |  |  D",
            "    +B-+  +--+"
    };
    cout << Solution().path(g_test) << endl;

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<string> g;
    string line;
    while(!input.eof()) {
        getline(input, line);
        g.push_back(line);
    }

    cout << Solution().path(g) << endl;

    input.close();

    return 0;
}