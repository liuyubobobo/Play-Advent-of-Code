/// http://adventofcode.com/2017/day/3
/// liuyubobobo
/// 2018-02-22

#include <iostream>
#include <cassert>

using namespace std;

class Solution{

public:
    int step(int num){

        if(num == 1)
            return 0;

        int side = 1;
        while(side * side < num)
            side += 2;

        int terminal_num = side * side;
        //cout << side << " " << terminal_num << endl;

        // bottom
        // terminal_num - bottom-right
        if(terminal_num >= num && num >= terminal_num - (side - 1))
            return (side - 1) / 2 + abs(terminal_num - (side - 1)/2 - num);

        // left
        // terminal_num - bottom-left
        terminal_num -= (side - 1);
        if(terminal_num >= num && num >= terminal_num - (side - 1))
            return (side - 1) / 2 + abs(terminal_num - (side - 1)/2 - num);

        // top
        // terminal_num - upper-left
        terminal_num -= (side - 1);
        if(terminal_num >= num && num >= terminal_num - (side - 1))
            return (side - 1) / 2 + abs(terminal_num - (side - 1)/2 - num);

        // right
        // terminal_num - upper-right
        terminal_num -= (side - 1);
        assert(terminal_num >= num && num >= terminal_num - (side - 2));
        return (side - 1) / 2 + abs(terminal_num - (side - 1)/2 - num);
    }
};

int main() {

    cout << Solution().step(361527) << endl;

    return 0;
}