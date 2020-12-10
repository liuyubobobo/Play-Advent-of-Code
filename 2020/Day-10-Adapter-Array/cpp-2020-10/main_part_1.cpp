/// Source : https://adventofcode.com/2020/day/10
/// Author : liuyubobobo
/// Time   : 2020-12-10

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_set>

using namespace std;


class Solution{

public:
    int solve(vector<int>& nums){

        sort(nums.begin(), nums.end());

        int cur = 0;
        vector<int> diff(4, 0);
        for(int e: nums)
            if(e == cur) continue;
            else if(e - cur <= 3) diff[e - cur] ++, cur = e;
            else break;

        diff[3] ++;
        cout << "diff1 : " << diff[1] << " diff3 : " << diff[3] << endl;
        return diff[1] * diff[3];
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 35
//    input.open("../../input_test_2.txt"); // 220
    assert(input.is_open());

    int x;
    vector<int> nums;
    while(!input.eof()){
        input >> x;
        nums.push_back(x);
    }

    cout << Solution().solve(nums) << endl;

    input.close();

    return 0;
}
