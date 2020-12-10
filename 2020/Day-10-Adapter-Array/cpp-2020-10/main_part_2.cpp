/// Source : https://adventofcode.com/2020/day/10#part2
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
    long long solve(vector<int>& nums){

        sort(nums.begin(), nums.end());
        for(int i = 1; i < nums.size(); i ++){
            assert(nums[i - 1] != nums[i]);
            assert(nums[i] - nums[i - 1] <= 3);
        }
        nums.push_back(nums.back() + 3);

        vector<long long> dp(nums.size(), 0ll);
        dp[0] = 1ll;
        dp[1] = dp[1] <= 3 ? 1ll : 0ll;
        dp[2] = dp[2] <= 3 ? 1ll : 0ll;
        for(int i = 1; i < nums.size(); i ++){
            if(i - 1 >= 0 && nums[i] - nums[i - 1] <= 3) dp[i] += dp[i - 1];
            if(i - 2 >= 0 && nums[i] - nums[i - 2] <= 3) dp[i] += dp[i - 2];
            if(i - 3 >= 0 && nums[i] - nums[i - 3] <= 3) dp[i] += dp[i - 3];
        }
        return dp.back();
    }
};


int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 8
//    input.open("../../input_test_2.txt"); // 19208
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
