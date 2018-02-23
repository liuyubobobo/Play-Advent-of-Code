/// http://adventofcode.com/2017/day/13
/// liuyubobobo
/// 2018-02-23

#include <iostream>
#include <fstream>
#include <cassert>
#include <map>
#include <sstream>

using namespace std;


class Solution{

public:
    int delay(const map<int, int>& scanners){

        for(int i = 0 ; ; i ++)
            if(!caught(scanners, i))
                return i;
        assert(false);
    }

private:
    bool caught(const map<int, int>& scanners, int start_time){

        for(const pair<int, int>& p: scanners){
            //cout << p.first << " " << p.second << endl;
            int time = p.first + start_time;
            int range = p.second;
            int pos = time % (2 * range - 2);
            if(pos >= range)
                pos = 2 * range - 2 - pos;
            if(pos == 0)
                return true;
        }
        return false;
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string line;
    map<int, int> scanners;
    while(!input.eof()){
        getline(input, line);

        stringstream ss(line);
        string depth_str;
        int range;
        ss >> depth_str >> range;

        assert(depth_str[depth_str.size()-1] == ':');
        scanners[stoi(depth_str.substr(0, depth_str.size()-1))] = range;
    }

    cout << Solution().delay(scanners) << endl;

    input.close();

    return 0;
}