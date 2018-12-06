/// https://adventofcode.com/2018/day/2
/// liuyubobobo
/// 2018-12-05

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <unordered_map>

using namespace std;


class Solution{

public:
    int checksum(const vector<string>& codes){

        int two = 0, three = 0;
        for(const string& code: codes){
            unordered_map<char, int> freq;
            for(char c: code)
                freq[c] ++;

            bool has2 = false, has3 = false;
            for(const pair<char, int>& p: freq)
                if(p.second == 2)
                    has2 = true;
                else if(p.second == 3)
                    has3 = true;

            two += has2;
            three += has3;
        }
        return two * three;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    vector<string> codes;
    string s;
    while(!input.eof()){
        input >> s;
        codes.push_back(s);
    }
    cout << Solution().checksum(codes) << endl;

    input.close();

    return 0;
}