/// http://adventofcode.com/2017/day/9
/// liuyubobobo
/// 2018-02-23

#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

class Solution{

public:
    int garbage_number(const string& raw_line){

        string line = del_mark(raw_line);
        // cout << "line: " << line << endl;
        return del_garbage(line);
    }

private:

    int del_garbage(const string& line){

        int res = 0;
        int pos = 0;
        while(pos < line.size()){
            if(line[pos] == '<'){
                pos ++;
                while(line[pos] != '>'){
                    res ++;
                    pos ++;
                }
            }
            pos ++;
        }

        return res;
    }

    string del_mark(const string& line){
        string res = "";

        int pos = 0;
        while(pos < line.size()){
            if(line[pos] != '!'){
                res += line[pos];
                pos ++;
            }
            else
                pos += 2;
        }

        return res;
    }
};

int main() {

    cout << Solution().garbage_number("<>") << endl;
    cout << Solution().garbage_number("<random characters>") << endl;
    cout << Solution().garbage_number("<<<<>") << endl;
    cout << Solution().garbage_number("<{!>}>") << endl;
    cout << Solution().garbage_number("<!!>") << endl;
    cout << Solution().garbage_number("<!!!>>") << endl;
    cout << Solution().garbage_number("<{o\"i!a,<{i<a>") << endl;

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string line;
    getline(input, line);

    cout << Solution().garbage_number(line) << endl;

    input.close();

    return 0;
}