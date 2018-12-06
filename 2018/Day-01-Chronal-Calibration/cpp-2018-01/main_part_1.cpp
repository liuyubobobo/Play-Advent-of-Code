/// https://adventofcode.com/2018/day/1
/// liuyubobobo
/// 2018-12-05

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <numeric>

using namespace std;


class Solution{

public:
    int chronalCalibration(const vector<int>& nums){

//        for(int x: nums)
//            cout << x << endl;
        return accumulate(nums.begin(), nums.end(), 0);
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    vector<int> nums;
    int x;
    while(!input.eof()){
        input >> x;
        nums.push_back(x);
    }
    cout << Solution().chronalCalibration(nums) << endl;

    input.close();

    return 0;
}