/// Source : https://adventofcode.com/2019/day/1
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

    int x, res = 0;
    while(!input.eof()){
        input >> x;
        res += (x / 3 - 2);
    }
    cout << res << endl;

    input.close();

    return 0;
}
