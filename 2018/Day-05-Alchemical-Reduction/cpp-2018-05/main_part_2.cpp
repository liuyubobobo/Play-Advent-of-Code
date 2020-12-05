/// https://adventofcode.com/2018/day/5#part2
/// liuyubobobo
/// 2020-12-05

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <stack>

using namespace std;


class Solution{

public:
    int solve(const string& line){

        int res = INT_MAX;
        for(char t = 'a'; t <= 'z'; t ++){
            string s = "";
            for(char c: line)
                if(tolower(c) != t) s += c;
            res = min(res, go(s));
        }
        return res;
    }

    int go(const string& line){

        stack<char> stack;
        for(char c: line){
            if(!stack.empty() && ok(stack.top(), c))
                stack.pop();
            else
                stack.push(c);
        }
        return stack.size();
    }

private:
    bool ok(char a, char b){
        return tolower(a) == tolower(b) && a != b;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string line;
    input >> line;
    cout << Solution().solve(line) << endl;

    input.close();

    return 0;
}