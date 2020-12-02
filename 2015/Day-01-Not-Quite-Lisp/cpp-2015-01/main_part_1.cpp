/// Source : https://adventofcode.com/2015/day/1
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

    int res = 0;
    for(char c: s) if(c == '(') res ++; else res --;
    cout << res << endl;

    input.close();

    return 0;
}
