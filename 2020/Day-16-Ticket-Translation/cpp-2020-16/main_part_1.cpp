/// Source : https://adventofcode.com/2020/day/16
/// Author : liuyubobobo
/// Time   : 2020-12-16

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;


class Solution{

public:
    int solve(unordered_map<string, vector<pair<int, int>>>& table,
               vector<vector<int>>& tickets){

        int res = 0;
        for(const vector<int>& v: tickets)
            for(int e: v)
                if(!valid(table, e)) res += e;
        return res;
    }

private:
    bool valid(unordered_map<string, vector<pair<int, int>>>& table, int e){

        for(const pair<string, vector<pair<int, int>>>& p: table)
            for(const pair<int, int>& interval: p.second)
                if(interval.first <= e && e <= interval.second)
                    return true;
        return false;
    }
};


pair<int, int> get_pair(const string& s){

    int hindex = s.find('-');
    int a = atoi(s.substr(0, hindex).c_str());
    int b = atoi(s.substr(hindex + 1).c_str());
    return {a, b};
}

vector<int> get_nums(const string& s){

    vector<int> v;
    for(int start = 0, i = start + 1; i <= s.size(); i ++)
        if(i == s.size() || s[i] == ','){
            v.push_back(atoi(s.substr(start, i - start).c_str()));
            start = i + 1;
            i = start;
        }
    return v;
}

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 71
    assert(input.is_open());

    unordered_map<string, vector<pair<int, int>>> table;
    string line;
    while(true){
        getline(input, line);
        if(line == "") break;

        int cindex = line.find(':');
        assert(cindex != string::npos);

        string field_name = line.substr(0, cindex);
        string num_field = line.substr(cindex + 2);

        int orindex = num_field.find("or");
        assert(orindex != string::npos);

//        cout << field_name << " " << num_field.substr(0, orindex - 1) << " " << num_field.substr(orindex + 3) << endl;

        table[field_name].push_back(get_pair(num_field.substr(0, orindex - 1)));
        table[field_name].push_back(get_pair(num_field.substr(orindex + 3)));
    }

    getline(input, line);
    getline(input, line);
    vector<int> your_ticket = get_nums(line);
    getline(input, line);
    assert(line == "");

    getline(input, line);
    vector<vector<int>> nearby_tickets;
    while(!input.eof()){
        getline(input, line);
//        cout << line << endl;
        nearby_tickets.push_back(get_nums(line));
    }

    cout << Solution().solve(table, nearby_tickets) << endl;

    input.close();

    return 0;
}
