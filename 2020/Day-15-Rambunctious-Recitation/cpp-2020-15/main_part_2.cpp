/// Source : https://adventofcode.com/2020/day/15#part2
/// Author : liuyubobobo
/// Time   : 2020-12-15

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


class Solution{

public:
    int solve(const vector<int>& nums, int k){

        unordered_map<int, int> table;
        for(int i = 0; i < nums.size(); i ++)
            table[nums[i]] = i;

        int next = 0;
        for(int i = nums.size(); i < k - 1; i ++){
            if(table.count(next)) {
                int tnext = i - table[next];
                table[next] = i;
                next = tnext;
            }
            else{
                table[next] = i;
                next = 0;
            }
        }
        return next;
    }
};

int main() {

//    vector<int> nums1 = {0, 3, 6};
//    cout << Solution().solve(nums1) << endl; // 436

    vector<int> nums = {2,0,1,7,4,14,18};
    cout << Solution().solve(nums, 30000000) << endl;

    return 0;
}
