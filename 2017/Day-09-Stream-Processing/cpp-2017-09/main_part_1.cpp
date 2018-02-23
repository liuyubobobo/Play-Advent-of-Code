/// http://adventofcode.com/2017/day/9
/// liuyubobobo
/// 2018-02-23

#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

class Solution{

public:
    int score(const string& raw_line){

        string line = del_mark(raw_line);
        // cout << "line: " << line << endl;
        string clean_line = del_garbage(line);
        // cout << "clean line: " << clean_line << endl;
        string process_line = del_others(clean_line);
        // cout << process_line << endl;

        if(process_line.size() == 0)
            return 0;

        assert(process_line[0] == '{');

        int res = 0;
        int stack = 0;
        for(char c: process_line)
            if(c == '{'){
                stack ++;
                res += stack;
            }
            else{
                assert(c == '}');
                stack --;
            }

        assert(stack == 0);
        return res;
    }

private:
    string del_others(const string& line){

        string res = "";
        for(char c: line)
            if(c == '{' || c == '}')
                res += c;
        return res;
    }

    string del_garbage(const string& line){

        string res = "";
        int pos = 0;
        while(pos < line.size()){
            if(line[pos] == '<'){
                while(line[pos] != '>')
                    pos ++;
            }
            else
                res += line[pos];
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

//    cout << Solution().score("{}") << endl;
//    cout << Solution().score("{{{}}}") << endl;
//    cout << Solution().score("{{},{}}") << endl;
//    cout << Solution().score("{{{},{},{{}}}}") << endl;
//    cout << Solution().score("{<a>,<a>,<a>,<a>}") << endl;
//    cout << Solution().score("{{<ab>},{<ab>},{<ab>},{<ab>}}") << endl;
//    cout << Solution().score("{{<!!>},{<!!>},{<!!>},{<!!>}}") << endl;
//    cout << Solution().score("{{<a!>},{<a!>},{<a!>},{<ab>}}") << endl;

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string line;
    getline(input, line);

    cout << Solution().score(line) << endl;

    input.close();

    return 0;
}