/// http://adventofcode.com/2017/day/2
/// liuyubobobo
/// 2018-02-22

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution{

public:
    int checksum(const vector<vector<int>>& table){

        int res = 0;
        for(const vector<int>& row: table){
            unordered_set<int> num_set;
            for(int num: row)
                num_set.insert(num);

            for(int num: row){
                vector<int> factors = get_factors(num);
                for(int f: factors)
                    if(num_set.find(f) != num_set.end()){
                        res += num / f;
                        goto next;
                    }
            }

            next:;
        }
        return res;
    }

private:
    vector<int> get_factors(int num){
        vector<int> ret;
        for(int i = 2 ; i*i <= num ; i ++)
            if(num % i == 0){
                ret.push_back(i);
                if(i*i != num)
                    ret.push_back(num / i);
            }
        return ret;
    }
};


void print_table(const vector<vector<int>>& table){

    for(const vector<int>& row: table){
        for(int num: row)
            cout << num << " ";
        cout << endl;
    }
}

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<vector<int>> table;
    string line;
    while(!input.eof()){
        getline(input, line);
        if(line == "")
            break;

        vector<int> row;
        stringstream ss(line);
        string num;
        while(ss >> num)
            row.push_back(stoi(num));

        table.push_back(row);
    }

    // print_table(table);

    cout << Solution().checksum(table) << endl;

    input.close();

    return 0;
}