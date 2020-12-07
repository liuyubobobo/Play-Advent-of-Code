/// Source : https://adventofcode.com/2019/day/5#part2
/// Author : liuyubobobo
/// Time   : 2020-12-07

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;


class Solution{

public:
    int solve(vector<int>& code){

        int cur = 0, ret;
        while(code[cur] != 99){
            if(code[cur] == 3){
                code[code[cur + 1]] = 5;
                cur += 2;
            }
            else if(code[cur] % 100 == 4){
//                cout << code[code[cur + 1]] << endl;
                ret = code[code[cur + 1]];
                cur += 2;
            }
            else if(code[cur] % 100 <= 2){

                int x = code[cur];
                int op = x % 100; x /= 100;

                int mod1 = x % 10; x /= 10;
                if(mod1 < 0 || mod1 > 1){cout << cur << " : " << mod1 << endl; assert(false);}

                int mod2 = x % 10; x /= 10;
                if(mod2 < 0 || mod2 > 1){cout << cur << " : " << mod1 << endl; assert(false);}

                int mod3 = x;        assert(mod3 == 0);

                int p1 = mod1 == 0 ? code[code[cur + 1]] : code[cur + 1];
                int p2 = mod2 == 0 ? code[code[cur + 2]] : code[cur + 2];

                code[code[cur + 3]] = op == 1 ? p1 + p2 : p1 * p2;

                cur += 4;
            }
            else if(code[cur] % 100 <= 6){

                int x = code[cur];
                int op = x % 100; x /= 100;

                int mod1 = x % 10; x /= 10;
                if(mod1 < 0 || mod1 > 1){cout << cur << " : " << mod1 << endl; assert(false);}

                int mod2 = x % 10; x /= 10;
                if(mod2 < 0 || mod2 > 1){cout << cur << " : " << mod1 << endl; assert(false);}

                int p1 = mod1 == 0 ? code[code[cur + 1]] : code[cur + 1];
                int p2 = mod2 == 0 ? code[code[cur + 2]] : code[cur + 2];

                if(op == 5){
                    if(p1 != 0) cur = p2;
                    else cur += 3;
                }
                else{
                    if(p1 == 0) cur = p2;
                    else cur += 3;
                }
            }
            else{

                int x = code[cur];
                int op = x % 100; x /= 100;

                int mod1 = x % 10; x /= 10;
                if(mod1 < 0 || mod1 > 1){cout << cur << " : " << mod1 << endl; assert(false);}

                int mod2 = x % 10; x /= 10;
                if(mod2 < 0 || mod2 > 1){cout << cur << " : " << mod1 << endl; assert(false);}

                int mod3 = x;        assert(mod3 == 0);

                int p1 = mod1 == 0 ? code[code[cur + 1]] : code[cur + 1];
                int p2 = mod2 == 0 ? code[code[cur + 2]] : code[cur + 2];

                if(op == 7) code[code[cur + 3]] = p1 < p2 ? 1 : 0;
                else code[code[cur + 3]] = p1 == p2 ? 1 : 0;

                cur += 4;
            }
        }
        return ret;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string s;
    input >> s;

    vector<int> code;
    for(int start = 0, index = start + 1; index <= s.size(); index ++)
        if(index == s.size() || s[index] == ','){
            code.push_back(atoi(s.substr(start, index - start).c_str()));
            start = index + 1;
            index = start;
        }

    cout << Solution().solve(code) << endl;

    input.close();

    return 0;
}
