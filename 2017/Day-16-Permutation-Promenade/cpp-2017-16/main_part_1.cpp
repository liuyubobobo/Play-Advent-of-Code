/// http://adventofcode.com/2017/day/16
/// liuyubobobo
/// 2018-02-23

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>

using namespace std;


class Solution{

public:
    string dance(const vector<string>& moves){

        string s = "";
        for(int i = 0 ; i < 16; i ++)
            s += ('a' + i);
        // cout << s << endl;

        for(const string& move: moves){
            //cout << move << endl;
            if(move[0] == 's')
                s = spin(s, stoi(move.substr(1)));
            else if(move[0] == 'x'){
                int hash_pos = move.find('/', 1);
                assert(hash_pos != string::npos);
                int a = stoi(move.substr(1, hash_pos - 1));
                int b = stoi(move.substr(hash_pos + 1));
                swap(s[a], s[b]);
            }
            else if(move[0] == 'p'){
                assert(move.size() == 4 && move[2] == '/');
                char a = move[1];
                char b = move[3];

                int a_i = s.find(a);
                int b_i = s.find(b);
                assert(a_i != string::npos && b_i != string::npos);

                swap(s[a_i], s[b_i]);
            }
            else
                assert(false);
        }

        return s;
    }

private:
    string spin(const string& s, int num){
        return s.substr(s.size() - num) + s.substr(0, s.size() - num);
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string line;
    getline(input, line);

    for(int i = 0 ; i < line.size() ; i ++)
        if(line[i] == ',')
            line[i] = ' ';

    stringstream ss(line);
    string s;
    vector<string> moves;
    while(ss >> s)
        moves.push_back(s);

    cout << Solution().dance(moves) << endl;

    input.close();

    return 0;
}