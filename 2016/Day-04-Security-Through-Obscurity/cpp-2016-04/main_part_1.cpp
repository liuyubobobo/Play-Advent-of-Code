/// http://adventofcode.com/2016/day/4
/// liuyubobobo
/// 2018-03-18

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>

using namespace std;


class Solution{

public:
    int sum(const vector<string>& rooms){

        int res = 0;
        for(const string& line: rooms){
            int sectorID = check(line);
            if(sectorID != -1)
                res += sectorID;
        }
        return res;
    }

private:
    int check(const string& line){

        int first_digit = 0;
        for(; !isdigit(line[first_digit]); first_digit ++);
        assert(first_digit - 1 >= 0 && line[first_digit - 1] == '-');

        int left = first_digit;
        for(; line[left] != '[' ; left ++);
        assert(left + 1 < line.size() && isalpha(line[left + 1]));
        assert(line.substr(left + 1).size() == 6);
        assert(line[line.size() - 1] == ']');

        string s = line.substr(0, first_digit);
        int sectorID = stoi(line.substr(first_digit, left - first_digit));
        string res_s = line.substr(left + 1, 5);
//        cout << s << endl;
//        cout << sectorID << endl;
//        cout << res_s << endl;

        map<char, int> freq;
        for(char c: s)
            if(c != '-'){
                assert(isalpha(c) && islower(c));
                freq[c] ++;
            }

        if(freq.size() < 5)
            return -1;

        vector<pair<int, char>> res_v;
        for(const pair<char, int>& p: freq)
            res_v.push_back(make_pair(p.second, p.first));

        sort(res_v.begin(), res_v.end(), cmp);

        string res = "";
        for(int i = 0 ; i < 5 ; i ++)
            res += res_v[i].second;
        //cout << res << endl;

        sort(res.begin(), res.end());
        sort(res_s.begin(), res_s.end());
        // cout << res << " " << res_s << endl;

        return res_s == res ? sectorID : -1;
    }

    static bool cmp(const pair<int, char>& p1, const pair<int, char>& p2){
        if(p1.first != p2.first)
            return p1.first > p2.first;
        return p1.second < p2.second;
    }
};

int main() {

    vector<string> rooms_test = {
            "aaaaa-bbb-z-y-x-123[abxyz]",
            "a-b-c-d-e-f-g-h-987[abcde]",
            "not-a-real-room-404[oarel]",
            "totally-real-room-200[decoy]"
    };
    cout << Solution().sum(rooms_test) << endl;

    // ---

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string line;
    vector<string> rooms;
    while(!input.eof()) {
        input >> line;
        rooms.push_back(line);
    }

    cout << Solution().sum(rooms) << endl;

    input.close();

    return 0;
}