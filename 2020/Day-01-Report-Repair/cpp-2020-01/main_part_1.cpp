/// Source : https://adventofcode.com/2020/day/1
/// Author : liuyubobobo
/// Time   : 2020-12-01

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;


class Solution{

public:
    int solve(const vector<int>& nums){

        for(int i = 0; i < nums.size(); i ++)
            for(int j = i + 1; j < nums.size(); j ++)
                if(nums[i] + nums[j] == 2020) return nums[i] * nums[j];
        assert(false);
        return -1;
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
    cout << Solution().solve(nums) << endl;

    input.close();

    return 0;
}
