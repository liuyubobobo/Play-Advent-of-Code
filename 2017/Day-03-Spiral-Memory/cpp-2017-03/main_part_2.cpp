/// http://adventofcode.com/2017/day/3
/// liuyubobobo
/// 2018-02-22

#include <iostream>
#include <cassert>
#include <map>

using namespace std;


class Solution{

private:
    int d4[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
    int d8[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0},
                    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    map<pair<int, int>, int> matrix;

public:
    int first_larger_value(int num){

        if(num <= 0)
            return 1;

        matrix.clear();
        matrix[make_pair(0, 0)] = 1;

        int curx = 0, cury = 0;
        int step = 0;
        while(true){

            step ++;
            for(int i = 0; i < 2; i ++){

                for(int j = 0; j < step; j ++){
                    int newX = curx + d4[i][0];
                    int newY = cury + d4[i][1];
                    int newValue = get_value(newX, newY);
                    if(newValue > num)
                        return newValue;
                    matrix[make_pair(newX, newY)] = newValue;
                    //cout << newX << " " << newY << " " << newValue << endl;
                    curx = newX;
                    cury = newY;
                }
            }

            step ++;
            for(int i = 2; i < 4; i ++){

                for(int j = 0; j < step; j ++){
                    int newX = curx + d4[i][0];
                    int newY = cury + d4[i][1];
                    int newValue = get_value(newX, newY);
                    if(newValue > num)
                        return newValue;
                    matrix[make_pair(newX, newY)] = newValue;
                    //cout << newX << " " << newY << " " << newValue << endl;
                    curx = newX;
                    cury = newY;
                }
            }
        }

        assert(false);
    }

private:
    int get_value(int x, int y){

        int res = 0;
        for(int i = 0 ; i < 8 ; i ++){
            int newX = x + d8[i][0];
            int newY = y + d8[i][1];
            if(matrix.find(make_pair(newX, newY)) != matrix.end())
                res += matrix.find(make_pair(newX, newY))->second;
        }
        return res;
    }
};

int main() {

    cout << Solution().first_larger_value(361527) << endl;
    // 409870 too high

    return 0;
}