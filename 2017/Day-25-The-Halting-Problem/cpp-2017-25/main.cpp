/// http://adventofcode.com/2017/day/25
/// liuyubobobo
/// 2018-03-09

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>

using namespace std;

struct Move{

    int write_value, next_d, next_state;

    Move(){
        this->write_value = this->next_d = this->next_state = 0;
    }

    Move(int write_value, int next_d, int next_state){
        this->write_value = write_value;
        this->next_d = next_d;
        this->next_state = next_state;
    }
};


class Solution{

public:
    int checksum(int initial_state, int step,
                 map<pair<int, int>, Move>& trans){

        unordered_map<int, int> tape;
        pair<int, int> cur = make_pair(initial_state, 0);
        for(int i = 0 ; i < step ; i ++){

            int cur_value = tape[cur.second];
            int cur_state = cur.first;

            Move m = trans[make_pair(cur_state, cur_value)];

            tape[cur.second] = m.write_value;
            cur.first = m.next_state;
            cur.second += m.next_d;
        }

        int res = 0;
        for(const pair<int, int>& p: tape){
            assert(p.second == 0 || p.second == 1);
            res += p.second;
        }

        return res;
    }
};


int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string line;
    map<pair<int, int>, Move> trans;
    while(!input.eof()) {

        getline(input, line);
        //cout << line << endl;
        int state = line[line.size()-2] - 'A';

        for(int i = 0 ; i < 2 ; i ++) {
            getline(input, line);
            //cout << line << endl;
            int value = line[line.size() - 2] - '0';

            getline(input, line);
            //cout << line << endl;
            int write_value = line[line.size() - 2] - '0';

            getline(input, line);
            //cout << line << endl;
            int next_d = line[line.size() - 3] == 'h' ? 1 : -1;

            getline(input, line);
            //cout << line << endl;
            int next_state = line[line.size() - 2] - 'A';

            //cout << state << " " << value << "->" << write_value << " " << next_d << " " << next_state << endl;
            trans[make_pair(state, value)] = Move(write_value, next_d, next_state);
        }
        getline(input, line);
        //assert(line.size() == 0);
    }

    cout << Solution().checksum(0, 12208951, trans) << endl;

    input.close();

    return 0;
}