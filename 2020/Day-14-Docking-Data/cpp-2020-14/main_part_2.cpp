/// Source : https://adventofcode.com/2020/day/14#part2
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
    unordered_map<long long, long long> mem;

public:
    Program() : mask(36){}

    void update_mask(const string& s){
        assert(s.size() == 36);
        for(int i = 0; i < s.size(); i ++)
            mask[i] = s[i] == 'X' ? -1 : (s[i] - '0');
    }

    void set(int address, int value){

        vector<int> abit;
        while(address){
            abit.push_back(address % 2);
            address /= 2;
        }
        while(abit.size() != 36) abit.push_back(0);
        reverse(abit.begin(), abit.end());

        for(int i = 0; i < 36; i ++)
            if(mask[i] != 0) abit[i] = mask[i];

        dfs(abit, 0, value);
    }

    long long sum(){
        long long res = 0ll;
        for(const pair<int, long long>& p: mem)
            res += p.second;
        return res;
    }

private:
    void dfs(vector<int>& abit, int index, long long value){

        if(index == 36){
            long long address = 0ll;
            for(int bit: abit) address = address * 2ll + (long long)bit;
            mem[address] = value;
            return;
        }

        if(abit[index] != -1){
            dfs(abit, index + 1, value);
            return;
        }

        abit[index] = 0;
        dfs(abit, index + 1, value);

        abit[index] = 1;
        dfs(abit, index + 1, value);

        abit[index] = -1;
    }
};


int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 295
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
