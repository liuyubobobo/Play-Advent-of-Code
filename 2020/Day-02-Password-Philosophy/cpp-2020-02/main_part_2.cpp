/// Source : https://adventofcode.com/2020/day/2#part2
/// Author : liuyubobobo
/// Time   : 2020-12-02

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;


void get_i_j(const string& s, int& l, int& r){

    int index = s.find('-');
    assert(index != string::npos);

    l = atoi(s.substr(0, index).c_str());
    r = atoi(s.substr(index + 1).c_str());
}

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string a, b, s;
    int res = 0;
    while(!input.eof()){
        input >> a >> b >> s;

        int i, j;
        get_i_j(a, i, j);

        char ch = b[0];
        assert(b.size() == 2 && b[1] == ':');

        assert(i - 1 >= 0 && i - 1 < s.size() && j - 1 >= 0 && j - 1 < s.size());
        res += ((s[i - 1] == ch) + (s[j - 1] == ch) == 1);
    }
    cout << res << endl;

    input.close();

    return 0;
}
