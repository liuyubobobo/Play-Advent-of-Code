/// Source : https://adventofcode.com/2020/day/14
/// Author : liuyubobobo
/// Time   : 2020-12-15

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;


class Program{

private:
    vector<int> mask;
    unordered_map<int, long long> mem;

public:
    Program() : mask(36){}

    void update_mask(const string& s){
        assert(s.size() == 36);
        for(int i = 0; i < s.size(); i ++)
            mask[i] = s[i] == 'X' ? -1 : (s[i] - '0');
    }

    void set(int address, int value){

        vector<int> vbit;
        while(value){
            vbit.push_back(value % 2);
            value /= 2;
        }
        while(vbit.size() != 36) vbit.push_back(0);
        reverse(vbit.begin(), vbit.end());

        for(int i = 0; i < 36; i ++)
            if(mask[i] != -1) vbit[i] = mask[i];

        long long res = 0ll;
        for(int bit: vbit) res = res * 2ll + (long long)bit;
        mem[address] = res;
    }

    long long sum(){
        long long res = 0ll;
        for(const pair<int, long long>& p: mem)
            res += p.second;
        return res;
    }
};


int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    Program program;
    string line;
    while(!input.eof()){
        getline(input, line);
//        cout << line << endl;
        if(line.substr(0, 4) == "mask"){
            string mask = line.substr(7);
            assert(mask.size() == 36);
            program.update_mask(mask);
        }
        else{
            assert(line.substr(0, 4) == "mem[");
            int l = line.find('['), r = line.find(']'), e = line.find('=');
            assert(l != string::npos && r != string::npos && e != string::npos);
            int address = atoi(line.substr(l + 1, r - (l + 1)).c_str());
            int value = atoi(line.substr(e + 2).c_str());
            if(value >= 2e9) assert(false);
            program.set(address, value);
        }
    }
    cout << program.sum() << endl;

    input.close();

    return 0;
}
