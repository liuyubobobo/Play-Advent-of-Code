/// Source : https://adventofcode.com/2020/day/9
/// Author : liuyubobobo
/// Time   : 2020-12-08

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_set>

using namespace std;


class Solution{

public:
    long long solve(const vector<long long>& nums){

        for(int i = 25; i < nums.size(); i ++)
            if(!ok(vector<long long>(nums.begin() + (i - 25), nums.begin() + i), nums[i]))
                return nums[i];
        return -1;
    }

private:
    bool ok(const vector<long long>& v, long long x){
        for(int i = 0; i < v.size(); i ++)
            for(int j = i + 1; j < v.size(); j ++)
                if(v[i] + v[j] == x) return true;
        return false;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    long long num;
    vector<long long> nums;
    while(!input.eof()){
        input >> num;
        nums.push_back(num);
    }

    cout << Solution().solve(nums) << endl;

    input.close();

    return 0;
}
