/// Source : https://adventofcode.com/2020/day/18
/// Author : liuyubobobo
/// Time   : 2020-12-18

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;


class Solution{

public:
    long long eval(const string& line){

        cout << line;
        vector<pair<char, long long>> stack;
        for(int i = 0; i < line.size(); i ++){
            char c = line[i];
            if(isdigit(c) && i) assert(!isdigit(line[i - 1]));
            if(c != ' '){
                if(isdigit(c)){
                    if(stack.empty() || stack.back().first == '(')
                        stack.push_back({'#', (long long)(c - '0')});
                    else{
                        stack.push_back({'#', (long long)(c - '0')});
                        inner_eval(stack);
                    }
                }
                else{
                    if(c != ')') stack.push_back({c, -1ll});
                    else{
                        assert(!stack.empty() && stack.back().first == '#');
                        long long x = stack.back().second;
                        stack.pop_back();

                        assert(!stack.empty() && stack.back().first == '(');
                        stack.pop_back();

                        stack.push_back({'#', x});
                        inner_eval(stack);
                    }
                }
            }
        }
        assert(stack.size() == 1 && stack[0].first == '#');
        cout << " = " << stack[0].second << endl;
        return stack[0].second;
    }

private:
    void inner_eval(vector<pair<char, long long>>& stack){

        if(stack.size() == 1) return;

        assert(stack.size() >= 2);
        if(stack[stack.size() - 2].first == '(') return;

        assert(!stack.empty() && stack.back().first == '#');
        long long y = stack.back().second;
        stack.pop_back();

        char op = stack.back().first;
        stack.pop_back();

        assert(!stack.empty() && stack.back().first == '#');
        long long x = stack.back().second;
        stack.pop_back();

        if(op == '+') stack.push_back({'#', x + y});
        else if(op == '-') stack.push_back({'#', x - y});
        else if(op == '*') stack.push_back({'#', x * y});
        else if(op == '/') stack.push_back({'#', x / y});

        return;
    }
};

int main() {

//    Solution().eval("1 + 2 * 3 + 4 * 5 + 6"); // 71
//    Solution().eval("2 * 3 + (4 * 5)"); // 26
//    Solution().eval("5 + (8 * 3 + 9 + 3 * 4 * 3)"); // 437
//    Solution().eval("5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))"); // 12240
//    Solution().eval("((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2"); // 13632

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 112
    assert(input.is_open());

    string line;
    long long res = 0ll;
    while(!input.eof()){
        getline(input, line);
        res += Solution().eval(line);
    }
    cout << res << endl;

    input.close();

    return 0;
}
