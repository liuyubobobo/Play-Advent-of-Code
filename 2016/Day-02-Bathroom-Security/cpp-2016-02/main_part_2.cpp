/// http://adventofcode.com/2016/day/2
/// liuyubobobo
/// 2018-03-18

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution{

private:
    const string keyboard[7] = {"       ",
                                "   1   ",
                                "  234  ",
                                " 56789 ",
                                "  ABC  ",
                                "   D   ",
                                "       "};
    const int d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

public:
    string code(const vector<string>& documents){

        string res = "";
        for(const string& line: documents)
            res += execute(line);
        return res;
    }

private:
    char execute(const string& line){

        int x = 3 , y = 1;
        for(char c: line){
            int newX = x + d[getd(c)][0];
            int newY = y + d[getd(c)][1];
            if(keyboard[newX][newY] != ' '){
                x = newX;
                y = newY;
            }
        }

        return keyboard[x][y];
    }

    int getd(char c){
        switch(c){
            case 'U': return 0;
            case 'R': return 1;
            case 'D': return 2;
            case 'L': return 3;
            default: assert(false);
        }
        return ' ';
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string line;
    vector<string> documents;
    while(!input.eof()) {
        input >> line;
        documents.push_back(line);
    }

    cout << Solution().code(documents) << endl;

    input.close();

    return 0;
}