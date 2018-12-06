/// https://adventofcode.com/2018/day/1
/// liuyubobobo
/// 2018-12-05

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <unordered_set>

using namespace std;


class Solution{

public:
    int firstFrequencyReachesTwice(const vector<int>& nums){

        unordered_set<int> seen;
        int f = 0;
        seen.insert(f);
        while(true){
            for(int x: nums){
                f += x;
                if(seen.count(f))
                    return f;
                seen.insert(f);
            }
        }
        cout << "No Frequency Reaches Twice" << endl;
        return -1;
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<int> nums;
    int x;
    while(!input.eof()){
        input >> x;
        nums.push_back(x);
    }
    cout << Solution().firstFrequencyReachesTwice(nums) << endl;

    input.close();

    return 0;
}