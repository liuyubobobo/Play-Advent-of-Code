/// http://adventofcode.com/2016/day/3
/// liuyubobobo
/// 2018-03-18

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution{

public:
    int triangle_num(const vector<vector<int>>& triangles){

        int res = 0;
        for(const vector<int>& triangle: triangles)
            if(is_triangle(triangle))
                res ++;
        return res;
    }

private:
    bool is_triangle(const vector<int>& triangle){

        if(triangle.size() != 3)
            return false;

        if(triangle[0] <= 0 || triangle[1] <= 0 || triangle[2] <= 0)
            return false;

        return triangle[0] + triangle[1] > triangle[2] &&
               abs(triangle[0] - triangle[1]) < triangle[2];
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string line;
    int num[3][3];
    vector<vector<int>> triangles;
    while(!input.eof()) {

        for(int i = 0 ; i < 3 ; i ++) {
            getline(input, line);
            stringstream ss(line);

            ss >> num[0][i] >> num[1][i] >> num[2][i];
        }

        for(int i = 0 ; i < 3 ; i ++)
            triangles.push_back({num[i][0], num[i][1], num[i][2]});
    }

    cout << Solution().triangle_num(triangles) << endl;

    input.close();

    return 0;
}