/// http://adventofcode.com/2017/day/23
/// liuyubobobo
/// 2018-02-23

#include <iostream>
#include <vector>

using namespace std;


class Solution{

private:
    const int turns = 50000000;

public:
    int spinlock(int step){

        int len = 2;
        int res = 1;

        int cur = 1, index = 2;
        for(index = 2 ; index <= turns ; index ++){

            cur = (cur + step) % len;
            if(cur == 0)
                res = index;
            cur ++;
            len ++;
        }

        return res;
    }
};

int main() {

    cout << Solution().spinlock(3) << endl;
    cout << Solution().spinlock(316) << endl;

    return 0;
}