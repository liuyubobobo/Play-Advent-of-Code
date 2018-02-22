/// http://adventofcode.com/2017/day/5
/// liuyubobobo
/// 2018-02-22

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

class Solution{

public:
    int step(vector<int>& offsets){

        int cur = 0;
        int res = 0;
        while(cur >= 0 && cur < offsets.size()){
            int prev = cur;
            cur += offsets[cur];
            if(offsets[prev] >=3)
                offsets[prev] -= 1;
            else
                offsets[prev] += 1;
            res ++;
        }

        return res;
    }
};


void print_vec(const vector<int>& vec){
    for(int num: vec)
        cout << num << " ";
    cout << endl;
}

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<int> offsets;
    int num;
    while(!input.eof()){
        input >> num;
        offsets.push_back(num);
    }

    // print_vec(offsets);

    cout << Solution().step(offsets) << endl;

    input.close();

    return 0;
}