/// Source : https://adventofcode.com/2015/day/5
/// Author : liuyubobobo
/// Time   : 2020-12-03

#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_set>

using namespace std;


class Solution{

public:
    bool is_nice(const string& s){

        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        int vowel_cnt = 0;
        for(char c: s)
            vowel_cnt += vowels.count(c);
        if(vowel_cnt < 3) return false;

        bool repeat = false;
        for(int i = 1; i < s.size(); i ++)
            if(s[i - 1] == s[i]){
                repeat = true;
                break;
            }
        if(!repeat) return false;

        if(s.find("ab") != string::npos) return false;
        if(s.find("cd") != string::npos) return false;
        if(s.find("pq") != string::npos) return false;
        if(s.find("xy") != string::npos) return false;
        return true;

    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string s;
    int res = 0;
    while(!input.eof()){
        input >> s;
        res += Solution().is_nice(s);
    }
    cout << res << endl;
    input.close();

    return 0;
}
