/// Source : https://adventofcode.com/2020/day/13
/// Author : liuyubobobo
/// Time   : 2020-12-14

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_set>

using namespace std;


class Solution{

public:
    int solve(int T, vector<int>& buses){

        int t = INT_MAX, res = -1;
        for(int id: buses){
            if(T % id == 0) return 0;
            else if((T / id + 1) * id - T < t)
                t = (T / id + 1) * id - T, res = t * id;
        }
        return res;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 295
    assert(input.is_open());

    int T;
    string line;
    input >> T >> line;

    vector<int> buses;
    for(int start = 0, i = start + 1; i <= line.size(); i ++)
        if(i == line.size() || line[i] == ','){

            string x = line.substr(start, i - start);
            if(x != "x"){
                int id = atoi(x.c_str());
                buses.push_back(id);
            }

            start = i + 1;
            i = start;
        }
    cout << Solution().solve(T, buses) << endl;

    input.close();

    return 0;
}
