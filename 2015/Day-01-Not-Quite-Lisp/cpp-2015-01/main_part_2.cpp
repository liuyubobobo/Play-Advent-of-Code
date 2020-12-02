/// Source : https://adventofcode.com/2015/day/1#part2
/// Author : liuyubobobo
/// Time   : 2020-12-02

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;


int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string s;
    input >> s;

    int res = 0, pos = 1;
    for(int i = 0; i < s.size(); i ++) {
        if(s[i] == '(') res ++;
        else res --;
        if(res < 0){
            pos = i + 1;
            break;
        }
    }
    cout << pos << endl;

    input.close();

    return 0;
}
