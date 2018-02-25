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
#include <queue>

using namespace std;


class Program{

private:
    unordered_map<string, long long> registers;
    int cur = 0;
    vector<string> instructions;
    queue<long long> signals;

    queue<long long> res;
    int send_value;

public:
    Program(const vector<string>& input, int id){
        instructions.clear();
        for(string ins: input)
            instructions.push_back(ins);

        registers.clear();
        registers["p"] = (long long)id;

        while(!signals.empty())
            signals.pop();

        cur = 0;
        send_value = 0;
    }

    queue<long long> run(queue<long long>& new_signals){

        assert(signals.empty());

        while(!res.empty())
            res.pop();

        while(!new_signals.empty()){
            signals.push(new_signals.front());
            new_signals.pop();
        }

        do{
            assert(cur >= 0 && cur < instructions.size());
            ;
        }while(execute(instructions[cur]));

        assert(signals.empty());

        return res;
    }

    int get_send_value(){
        return send_value;
    }

private:
    bool execute(const string& instruction){

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
            if(!run_rcv(X))
                return false;
        }
        else if(ins == "jgz"){
            ss >> X >> Y;
            run_jgz(X, Y);
        }
        else{
            cout << "Error instruction: " << ins << endl;
            assert(false);
        }

        return true;
    }

    void run_snd(const string& X){
        res.push(get_num(X));
        cur ++;
        send_value ++;
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

        assert(isalpha(X[0]));

        if(signals.empty())
            return false;

        registers[X] = signals.front();
        signals.pop();
        cur ++;

        return true;
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

class Solution{

public:
    int send1(const vector<string>& instructions){

        Program p0(instructions, 0);
        Program p1(instructions, 1);

        queue<long long> empty;
        queue<long long> res0 = p0.run(empty);
        queue<long long> res1 = p1.run(empty);
        while(!res0.empty() || !res1.empty()){
            queue<long long> new_res0 = p0.run(res1);
            queue<long long> new_res1 = p1.run(res0);

            res0 = new_res0;
            res1 = new_res1;
        }

        return p1.get_send_value();
    }
};

int main() {

    vector<string> test = {
            "snd 1",
            "snd 2",
            "snd p",
            "rcv a",
            "rcv b",
            "rcv c",
            "rcv d"
    };
    cout << Solution().send1(test) << endl;

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

    cout << Solution().send1(instructions) << endl;

    input.close();

    return 0;
}