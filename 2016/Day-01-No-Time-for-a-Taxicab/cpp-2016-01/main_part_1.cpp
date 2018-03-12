/// http://adventofcode.com/2016/day/1
/// liuyubobobo
/// 2018-03-12

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution{

private:
    int d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

public:
    int away(const vector<string>& documents){

        int cur_x = 0, cur_y = 0, cur_d = 0;
        for(const string& s: documents){

            if(s[0] == 'R')
                cur_d = (cur_d + 1) % 4;
            else{
                assert(s[0] == 'L');
                cur_d = (cur_d + 3) % 4;
            }

            int step = stoi(s.substr(1));
            cur_x += step * d[cur_d][0];
            cur_y += step * d[cur_d][1];
        }

        return abs(cur_x) + abs(cur_y);
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