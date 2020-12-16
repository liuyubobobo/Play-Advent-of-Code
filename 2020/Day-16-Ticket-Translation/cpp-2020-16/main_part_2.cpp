/// Source : https://adventofcode.com/2020/day/16#part2
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
    long long solve(vector<pair<string, vector<pair<int, int>>>>& table,
                    vector<vector<int>>& tickets, vector<int>& your_ticket){

//        cout << tickets.size() << endl;
        vector<vector<int>> data;
        for(const vector<int>& v: tickets){
            bool ok = true;
            for(int e: v)
                if(!valid(table, e)){
                    ok = false; break;
                }
            if(ok) data.push_back(v);
        }
//        cout << data.size() << endl;
        assert(data[0].size() == table.size());
        for(const pair<string, vector<pair<int, int>>>& p: table)
            cout << p.first << " : "
                 << p.second[0].first << "-" << p.second[0].second << " , "
                 << p.second[1].first << "-" << p.second[1].second << endl;

        vector<vector<int>> possible(data[0].size());
        for(int j = 0; j < data[0].size(); j ++)
            for(int i = 0; i < table.size(); i ++)
                if(ok(data, j, table[i].second)) possible[j].push_back(i);

        for(int i = 0; i < possible.size(); i ++){
            cout << i << " : ";
            for(int e: possible[i]) cout << e << " "; cout << endl;
        }

        vector<int> order(data[0].size());
        vector<bool> used(data[0].size(), false);
        assert(dfs(order, 0, used, possible));

        cout << "order : ";
        for(int e: order) cout << e << " "; cout << endl;

//        vector<int> order = {16, 17, 5, 15, 2, 6, 9, 11, 1, 7, 19, 18, 0, 14, 3, 12, 13, 8, 10, 4};
        long long res = 1ll;
        for(int i = 0; i < data[0].size(); i ++){
            if(table[order[i]].first.substr(0, 9) == "departure")
                res *= (long long)your_ticket[i];
        }
        return res;
    }

private:
    bool dfs(vector<int>& order, int index, vector<bool>& used, const vector<vector<int>>& possible){

        if(index == order.size()) return true;

        for(int i: possible[index])
            if(!used[i]){
                used[i] = true;
                order[index] = i;
                if(dfs(order, index + 1, used, possible)) return true;
                used[i] = false;
            }
        return false;
    }

    bool ok(vector<vector<int>>& data, int col, vector<pair<int, int>>& range){

        for(const vector<int>& v: data){
            int e = v[col];
            bool ok = false;
            for(const pair<int, int>& p: range)
                if(p.first <= e && e <= p.second) ok = true;
            if(!ok) return false;
        }
        return true;
    }

    bool valid(vector<pair<string, vector<pair<int, int>>>>& table, int e){

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

    vector<pair<string, vector<pair<int, int>>>> table;
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

        vector<pair<int, int>> range;
        range.push_back(get_pair(num_field.substr(0, orindex - 1)));
        range.push_back(get_pair(num_field.substr(orindex + 3)));
        table.push_back({field_name, range});
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

    cout << Solution().solve(table, nearby_tickets, your_ticket) << endl;

    input.close();

    return 0;
}
