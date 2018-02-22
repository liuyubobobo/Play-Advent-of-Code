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

using namespace std;

class Solution{

public:
    int checksum(const vector<vector<int>>& table){

        int res = 0;
        for(const vector<int>& row: table){
            int max_num = *max_element(row.begin(), row.end());
            int min_num = *min_element(row.begin(), row.end());
            res += (max_num - min_num);
        }
        return res;
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