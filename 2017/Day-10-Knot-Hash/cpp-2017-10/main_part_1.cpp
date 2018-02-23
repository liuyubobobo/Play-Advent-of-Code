/// http://adventofcode.com/2017/day/10
/// liuyubobobo
/// 2018-02-23

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;


class Solution{

public:
    int result(const vector<int>& lengths){

        vector<int> numbers(256, 0);
        for(int i = 0 ; i < 256 ; i ++)
            numbers[i] = i;

        int cur = 0;
        int skip = 0;
        for(int length: lengths){

            vector<int> tvec;
            for(int i = 0; i < length; i ++)
                tvec.push_back(numbers[(cur + i) % 256]);
            reverse(tvec.begin(), tvec.end());

            for(int i = 0; i < length; i ++)
                numbers[(cur + i) % 256] = tvec[i];

            cur = (cur + length + skip) % 256;
            skip ++;
        }

        return numbers[0] * numbers[1];
    }
};


void printVec(const vector<int>& vec){
    for(int num: vec)
        cout << num << " ";
    cout << endl;
}

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string line;
    if(!input.eof())
        getline(input, line);

    for(int i = 0 ; i < line.size() ; i ++)
        if(line[i] == ',')
            line[i] = ' ';

    stringstream ss(line);
    vector<int> lengths;
    string num;
    while(ss >> num)
        lengths.push_back(stoi(num));

    // printVec(lengths);
    cout << Solution().result(lengths) << endl;

    input.close();

    return 0;
}