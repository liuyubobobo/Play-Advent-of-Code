/// http://adventofcode.com/2017/day/23
/// liuyubobobo
/// 2018-02-27

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
    int res = 0;

public:
    int mul_freq(const vector<string>& instructions){

        registers.clear();
        cur = 0;
        res = 0;
        while(cur >= 0 && cur < instructions.size()){
            //assert(cur >= 0 && cur < instructions.size());
            run(instructions[cur]);
        }

        return res;
    }

private:
    bool run(const string& instruction){

        // cout << instruction << endl;

        stringstream ss(instruction);

        string ins, X, Y;
        ss >> ins;
        if(ins == "set"){
            ss >> X >> Y;
            run_set(X, Y);
        }
        else if(ins == "sub"){
            ss >> X >> Y;
            run_sub(X, Y);
        }
        else if(ins == "mul"){
            ss >> X >> Y;
            run_mul(X, Y);
            res ++;
        }
        else if(ins == "jnz"){
            ss >> X >> Y;
            run_jnz(X, Y);
        }
        else{
            cout << "Error instruction: " << ins << endl;
            assert(false);
        }

        return false;
    }

    void run_set(const string& X, const string& Y){

        assert(isalpha(X[0]));
        registers[X] = get_num(Y);
        cur ++;
    }

    void run_sub(const string& X, const string& Y){

        assert(isalpha(X[0]));
        registers[X] -= get_num(Y);
        cur ++;
    }

    void run_mul(const string& X, const string& Y){

        assert(isalpha(X[0]));
        registers[X] *= get_num(Y);
        cur ++;
    }

    void run_jnz(const string& X, const string& Y){

        if(get_num(X) != (long long)0)
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

    cout << Solution().mul_freq(instructions) << endl;

    input.close();

    return 0;
}