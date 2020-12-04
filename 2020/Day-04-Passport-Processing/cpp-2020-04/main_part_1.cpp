/// Source : https://adventofcode.com/2020/day/4
/// Author : liuyubobobo
/// Time   : 2020-12-04

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_set>

using namespace std;


class Solution{

public:
    bool is_valid(const string& s){

        unordered_set<string> set;
        for(int start = 0, i = start + 1; i <= s.size(); i ++)
            if(i == s.size() || s[i] == ' '){
                string info = s.substr(start, i - start);

                int colon = info.find(':');
                assert(colon != string::npos);

                set.insert(info.substr(0, colon));

                start = i + 1;
                i = start;
            }

        vector<string> check = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
        for(const string& item: check) if(!set.count(item)) return false;
        return true;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test.txt");
    assert(input.is_open());

    string line, data = "";
    int res = 0;
    while(!input.eof()){
        getline(input, line);
        data += line;
        if(line == ""){
            res += Solution().is_valid(data);
            data = "";
        }
        else data += ' ';
    }
    res += Solution().is_valid(data);

    cout << res << endl;

    input.close();

    return 0;
}
