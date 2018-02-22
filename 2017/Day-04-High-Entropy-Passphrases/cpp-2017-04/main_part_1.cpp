/// http://adventofcode.com/2017/day/4
/// liuyubobobo
/// 2018-02-22

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>

using namespace std;

class Solution{

public:
    int valid_num(const vector<string>& passphrases){

        int res = 0;
        for(const string passphrase: passphrases)
            if(valid(passphrase))
                res += 1;
        return res;
    }

private:
    bool valid(const string& passphrase){

        unordered_set<string> table;
        stringstream ss(passphrase);
        string word;
        while(ss >> word){
            if(table.find(word) != table.end())
                return false;
            table.insert(word);
        }
        return true;
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<string> passphrases;
    string line;
    while(!input.eof()){
        getline(input, line);
        passphrases.push_back(line);
    }

    cout << Solution().valid_num(passphrases) << endl;

    input.close();

    return 0;
}