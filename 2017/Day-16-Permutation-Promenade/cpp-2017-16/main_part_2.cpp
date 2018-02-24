/// http://adventofcode.com/2017/day/16
/// liuyubobobo
/// 2018-02-23

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;


class Solution{

private:
    unordered_map<string, int> seen;
    vector<string> res;

public:
    string billion_dances(const vector<string>& moves){

        string s = "";
        for(int i = 0 ; i < 16; i ++)
            s += ('a' + i);

        seen.clear();
        seen[s] = 0;
        res.push_back(s);
        int index = 1;
        while(true){
            s = dance(moves, s);
            if(seen.find(s) == seen.end()){
                seen[s] = index;
                index ++;
                res.push_back(s);
            }
            else
                break;
        }

        int loop_start = seen[s];
        int loop_length = index - loop_start;
//        cout << "loop start: " << loop_start << endl;
//        cout << "loop length: " << loop_length << endl;

        long long turns = 1000000000;
//        cout << (int)((turns - (long long)loop_start) % (long long)loop_length) << endl;

        return res[(int)((turns - (long long)loop_start) % (long long)loop_length)];
    }

private:
    string dance(const vector<string>& moves, const string& s){

        string res = s;
        // cout << s << endl;

        for(const string& move: moves){
            //cout << move << endl;
            if(move[0] == 's')
                res = spin(res, stoi(move.substr(1)));
            else if(move[0] == 'x'){
                int hash_pos = move.find('/', 1);
                assert(hash_pos != string::npos);
                int a = stoi(move.substr(1, hash_pos - 1));
                int b = stoi(move.substr(hash_pos + 1));
                swap(res[a], res[b]);
            }
            else if(move[0] == 'p'){
                assert(move.size() == 4 && move[2] == '/');
                char a = move[1];
                char b = move[3];

                int a_i = res.find(a);
                int b_i = res.find(b);
                assert(a_i != string::npos && b_i != string::npos);

                swap(res[a_i], res[b_i]);
            }
            else
                assert(false);
        }

        return res;
    }

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

    cout << Solution().billion_dances(moves) << endl;

    input.close();

    return 0;
}