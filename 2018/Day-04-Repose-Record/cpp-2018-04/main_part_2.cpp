/// https://adventofcode.com/2018/day/4
/// liuyubobobo
/// 2020-12-03

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <string>

using namespace std;


class Solution{

public:
    int solve(vector<string>& records){

        sort(records.begin(), records.end());

        int curguard = -1, start = -1, end = -1;
        vector<unordered_map<int, int>> distribution(60);
        for(const string& s: records){
//            cout << s << endl;
            if(s[19] == 'G'){
                curguard = get_guard_id(s);
                assert(curguard != -1);

                start = -1;
            }
            else if(s[19] == 'f'){
                start = get_time(s);
                assert(start != -1);
            }
            else if(s[19] == 'w'){
                assert(start != -1);
                end = get_time(s);
                assert(end != -1);
                assert(end > start);

                for(int i = start; i < end; i ++)
                    distribution[i][curguard] ++;
            }
            else assert(false);
        }

        int most = 0, guard = -1, minute = -1;
        for(int i = 0; i < 60; i ++)
            for(const pair<int, int>& p: distribution[i])
                if(p.second > most) most = p.second, guard = p.first, minute = i;
        assert(guard != -1 && minute != -1);

        return guard * minute;
    }

private:
    int get_time(const string& s){

        int colon = s.find(':');
        assert(colon != string::npos);

        int start = colon + 1;
        for(int i = start + 1; i < s.size(); i ++)
            if(s[i] == ']')
                return atoi(s.substr(start, i - start).c_str());
        return -1;
    }

    int get_guard_id(const string& s){

        int sharp = s.find('#');
        assert(sharp != string::npos);

        int start = sharp + 1;
        for(int i = start + 1; i < s.size(); i ++)
            if(s[i] == ' ')
                return atoi(s.substr(start, i - start).c_str());
        return -1;
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    vector<string> records;
    string s;
    while(!input.eof()){
        getline(input, s);
        records.push_back(s);
    }
    cout << Solution().solve(records) << endl;

    input.close();

    return 0;
}