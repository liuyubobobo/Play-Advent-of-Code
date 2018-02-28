/// http://adventofcode.com/2017/day/22
/// liuyubobobo
/// 2018-02-27

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <set>

using namespace std;


class Solution{

private:
    set<pair<int, int>> infected;
    int d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

public:
    int infected_num(const vector<string>& raw_g, int max_iter){

        assert(raw_g.size() % 2 == 1);
        assert(raw_g.size() == raw_g[0].size());

        get_g(raw_g);

        pair<int, int> cur_pos = make_pair(raw_g.size() / 2, raw_g.size() / 2);
        int cur_d = 0;

        int res = 0;
        for(int i = 0; i < max_iter ; i ++){

            if(infected.find(cur_pos) != infected.end()){
                cur_d = (cur_d + 1) % 4;
                infected.erase(cur_pos);
            }
            else{
                cur_d --;
                if(cur_d < 0)
                    cur_d += 4;
                infected.insert(cur_pos);
                res ++;
            }

            cur_pos.first += d[cur_d][0];
            cur_pos.second += d[cur_d][1];
        }

        return res;
    }

private:
    void get_g(const vector<string>& raw_g){

        infected.clear();
        for(int i = 0 ; i < raw_g.size() ; i ++)
            for(int j = 0 ; j < raw_g[i].size() ; j ++)
                if(raw_g[i][j] == '#')
                    infected.insert(make_pair(i, j));
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<string> raw_g;
    string line;
    while(!input.eof()) {
        getline(input, line);
        raw_g.push_back(line);
    }

    cout << Solution().infected_num(raw_g, 10000) << endl;

    input.close();

    return 0;
}