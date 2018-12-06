/// https://adventofcode.com/2018/day/2
/// liuyubobobo
/// 2018-12-05

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;


class Solution{

public:
    string checksum(const vector<string>& codes){

        int n = codes.size();
        for(int i = 0; i < n; i ++)
            for(int j = i + 1; j < n; j ++)
                if(ok(codes[i], codes[j]))
                    return common(codes[i], codes[j]);
        return "";
    }

private:
    bool ok(const string& s1, const string& s2){

        if(s1.size() != s2.size())
            return false;

        int diff = 0;
        for(int i = 0; i < s1.size(); i ++){
            diff += (s1[i] != s2[i]);
            if(diff > 1)
                return false;
        }
        return diff == 1;
    }

    string common(const string& s1, const string& s2){
        for(int i = 0; i < s1.size(); i ++)
            if(s1[i] != s2[i])
                return s1.substr(0, i) + s2.substr(i + 1);
        return "";
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