/// http://adventofcode.com/2017/day/23
/// liuyubobobo
/// 2018-02-23

#include <iostream>
#include <vector>

using namespace std;

// Very slow solution
class Solution{

private:
    vector<int> val;
    vector<int> next;
    const int turns = 50000000;

public:
    int spinlock(int step){

        val.push_back(0);
        val.push_back(1);

        next.push_back(1);
        next.push_back(0);

        int cur = 1, index = 2;
        for(index = 2 ; index <= turns ; index ++){

            for(int i = 0 ; i < step ; i ++)
                cur = next[cur];

            int new_index = val.size();
            val.push_back(0);
            next.push_back(0);

            val[new_index] = index;
            next[new_index] = next[cur];
            next[cur] = new_index;

            cur = new_index;
        }

        return val[next[0]];
    }
};

int main() {

    // cout << Solution().spinlock(3) << endl;
    cout << Solution().spinlock(316) << endl;
    // 13326437

    return 0;
}