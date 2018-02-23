/// http://adventofcode.com/2017/day/11
/// liuyubobobo
/// 2018-02-23

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>

using namespace std;


class Solution{

public:
    int fewest_step(const vector<string>& paths){

        int x = 0, y = 0;
        for(const string& direction: paths){
            if(direction == "n")
                x -= 1;
            else if(direction == "ne")
                y += 1;
            else if(direction == "se")
                x += 1, y += 1;
            else if(direction == "s")
                x += 1;
            else if(direction == "sw")
                y -= 1;
            else if(direction == "nw")
                x -= 1, y -= 1;
            else
                assert(false);
        }

        int res1 = abs(x) + abs(y-x);
        int res2 = abs(y) + abs(x-y);
        return min(res1, res2);
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string line;
    getline(input, line);
    for(int i = 0 ; i < line.size() ; i ++)
        if(line[i] == ',')
            line[i] = ' ';

    stringstream ss(line);
    vector<string> paths;
    string direction;
    while(ss >> direction)
        paths.push_back(direction);

    cout << Solution().fewest_step(paths) << endl;

    input.close();

    return 0;
}