/// http://adventofcode.com/2017/day/8
/// liuyubobobo
/// 2018-02-22

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
    unordered_map<string, int> registers;

public:
    int max_val(const vector<string>& instructions){

        registers.clear();

        int res = 0;
        for(const string& instruction: instructions){

            stringstream ss(instruction);

            string register_name, sign, if_str, eval_val, eval_sign;
            int op_num, eval_num;

            ss >> register_name >> sign >> op_num;
            ss >> if_str >> eval_val >> eval_sign >> eval_num;

            if(eval(eval_val, eval_sign, eval_num)){
                if(registers.find(register_name) == registers.end())
                    registers[register_name] = 0;

                if(sign == "dec")
                    op_num = -op_num;
                else
                    assert(sign == "inc");

                registers[register_name] += op_num;

                for(const pair<string, int>& p: registers)
                    res = max(res, p.second);
            }
        }

        return res;
    }

private:
    bool eval(string name, string sign, int num){
        int val = 0;
        if(registers.find(name) != registers.end())
            val = registers.find(name)->second;
        else
            registers[name] = 0;

        if(sign == "==")
            return val == num;

        if(sign == "<")
            return val < num;

        if(sign == "<=")
            return val <= num;

        if(sign == ">")
            return val > num;

        if(sign == ">=")
            return val >= num;

        if(sign == "!=")
            return val != num;

        assert(false);
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<string> instructions;
    string line;
    while(!input.eof()){
        getline(input, line);
        instructions.push_back(line);
    }

    cout << Solution().max_val(instructions) << endl;

    input.close();

    return 0;
}