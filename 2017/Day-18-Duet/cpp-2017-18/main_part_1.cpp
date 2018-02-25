/// http://adventofcode.com/2017/day/18
/// liuyubobobo
/// 2018-02-25

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;


class Solution{

private:
    unordered_map<string, long long> registers;
    int cur = 0;
    long long last_freq = -1;

public:
    int recovered_freq(const vector<string>& instructions){

        registers.clear();
        last_freq = -1;
        cur = 0;
        while(true){
            assert(cur >= 0 && cur < instructions.size());
            if(run(instructions[cur]))
                return (int)last_freq;
        }

        assert(false);
    }

private:
    bool run(const string& instruction){

        // cout << instruction << endl;

        stringstream ss(instruction);

        string ins, X, Y;
        ss >> ins;
        if(ins == "snd"){
            ss >> X;
            run_snd(X);
        }
        else if(ins == "set"){
            ss >> X >> Y;
            run_set(X, Y);
        }
        else if(ins == "add"){
            ss >> X >> Y;
            run_add(X, Y);
        }
        else if(ins == "mul"){
            ss >> X >> Y;
            run_mul(X, Y);
        }
        else if(ins == "mod"){
            ss >> X >> Y;
            run_mod(X, Y);
        }
        else if(ins == "rcv"){
            ss >> X;
            if(run_rcv(X))
                return true;
        }
        else if(ins == "jgz"){
            ss >> X >> Y;
            run_jgz(X, Y);
        }
        else{
            cout << "Error instruction: " << ins << endl;
            assert(false);
        }

        return false;
    }

    void run_snd(const string& X){
        last_freq = get_num(X);
        // cout << "!!! play " << last_freq << endl;
        cur ++;
    }

    void run_set(const string& X, const string& Y){

        assert(isalpha(X[0]));
        registers[X] = get_num(Y);
        cur ++;
    }

    void run_add(const string& X, const string& Y){

        assert(isalpha(X[0]));
        registers[X] += get_num(Y);
        cur ++;
    }

    void run_mul(const string& X, const string& Y){

        assert(isalpha(X[0]));
        registers[X] *= get_num(Y);
        cur ++;
    }

    void run_mod(const string& X, const string& Y){

        assert(isalpha(X[0]));
        assert(registers[X] >= (long long)0);
        assert(get_num(Y) >= (long long)0);
        registers[X] %= get_num(Y);

        cur ++;
    }

    bool run_rcv(const string& X){

        cur ++;
        if(get_num(X) != (long long)0)
            return true;

        return false;
    }

    void run_jgz(const string& X, const string& Y){

        if(get_num(X) > (long long)0)
            cur += (int)get_num(Y);
        else
            cur ++;
    }

    long long get_num(const string& X){

        if(isalpha(X[0]))
            return registers[X];

        int start = 0;
        if(X[0] == '-')
            start = 1;

        long long res = (long long)0;
        for(int i = start ; i < X.size() ; i ++)
            res = res * (long long)10 + (long long)(X[i] - '0');

        if(X[0] == '-')
            res = -res;
        return res;
    }
};

int main() {

    vector<string> test = {
            "set a 1",
            "add a 2",
            "mul a a",
            "mod a 5",
            "snd a",
            "set a 0",
            "rcv a",
            "jgz a -1",
            "set a 1",
            "jgz a -2"
    };
    cout << Solution().recovered_freq(test) << endl;

    // ---

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<string> instructions;
    string line;
    while(!input.eof()) {
        getline(input, line);
        // cout << line << endl;
        instructions.push_back(line);
    }

    cout << Solution().recovered_freq(instructions) << endl;

    input.close();

    return 0;
}