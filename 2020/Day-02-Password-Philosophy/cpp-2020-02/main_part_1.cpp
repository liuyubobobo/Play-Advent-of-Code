/// Source : https://adventofcode.com/2020/day/2
/// Author : liuyubobobo
/// Time   : 2020-12-02

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;


class Solution{

public:
    bool is_valid(int l, int r, char ch, const string& s){

        vector<int> f(26, 0);
        for(char c: s) f[c - 'a'] ++;

        return l <= f[ch - 'a'] && f[ch - 'a'] <= r;
    }
};


void get_l_r(const string& s, int& l, int& r){

    int index = s.find('-');
    assert(index != string::npos);

    l = atoi(s.substr(0, index).c_str());
    r = atoi(s.substr(index + 1).c_str());
}

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string a, b, c;
    int res = 0;
    while(!input.eof()){
        input >> a >> b >> c;

        int l, r;
        get_l_r(a, l, r);

        char ch = b[0];
        assert(b.size() == 2 && b[1] == ':');

        res += Solution().is_valid(l, r, ch, c);
    }
    cout << res << endl;

    input.close();

    return 0;
}
