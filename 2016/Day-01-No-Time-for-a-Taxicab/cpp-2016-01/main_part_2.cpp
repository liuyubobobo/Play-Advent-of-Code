/// http://adventofcode.com/2016/day/1
/// liuyubobobo
/// 2018-03-12

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution{

private:
    int d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

public:
    int away(const vector<string>& documents){

        set<pair<int, int>> visited;
        visited.insert(make_pair(0, 0));

        pair<int, int> cur_pos = make_pair(0, 0);
        int cur_d = 0;
        for(const string& s: documents){

            if(s[0] == 'R')
                cur_d = (cur_d + 1) % 4;
            else{
                assert(s[0] == 'L');
                cur_d = (cur_d + 3) % 4;
            }

            int step = stoi(s.substr(1));
            for(int i = 1 ; i <= step ; i ++){
                cur_pos.first += d[cur_d][0];
                cur_pos.second += d[cur_d][1];
                if(visited.find(cur_pos) != visited.end())
                    return abs(cur_pos.first) + abs(cur_pos.second);
                else
                    visited.insert(cur_pos);
            }
        }

        assert(false);
        return -1;
    }
};


int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string line;
    vector<string> documents;
    while(!input.eof()) {

        input >> line;
        if(line[line.size()-1] == ',')
            line = line.substr(0, line.size() - 1);
        documents.push_back(line);
    }

    cout << Solution().away(documents) << endl;

    input.close();
    
    return 0;
}