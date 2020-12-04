/// Source : https://adventofcode.com/2020/day/4
/// Author : liuyubobobo
/// Time   : 2020-12-04

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

using namespace std;


class Solution{

public:
    bool is_valid(const string& s){

        unordered_map<string, string> map;
        for(int start = 0, i = start + 1; i <= s.size(); i ++)
            if(i == s.size() || s[i] == ' '){
                string info = s.substr(start, i - start);

                int colon = info.find(':');
                assert(colon != string::npos);

                map[info.substr(0, colon)] = info.substr(colon + 1);

                start = i + 1;
                i = start;
            }

        vector<string> check = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
        for(const string& item: check) if(!map.count(item)) return false;

        if(!check_year_ok(map["byr"], 1920, 2002)) return false;
        if(!check_year_ok(map["iyr"], 2010, 2020)) return false;
        if(!check_year_ok(map["eyr"], 2020, 2030)) return false;
        if(!check_height_ok(map["hgt"])) return false;
        if(!check_hair_color_ok(map["hcl"])) return false;
        if(!check_eye_color_ok(map["ecl"])) return false;
        if(!check_pid_ok(map["pid"])) return false;

        return true;
    }

private:
    bool is_number(const string& s, int base){

        for(char c: s)
            if(base == 10){
                if(!('0' <= c && c <= '9')) return false;
            }
            else if(base == 16){
                if(!(('0' <= c && c <= '9') || ('a' <= c && c <= 'f'))) return false;
            }
        return true;
    }

    bool check_year_ok(const string& s, int l, int r){
        if(!is_number(s, 10)) return false;
        int t = atoi(s.c_str());
        return l <= t && t <= r;
    }

    bool check_height_ok(const string& s){

        if(s.size() < 3) return false;

        string num_str = s.substr(0, s.size() - 2);
        if(!is_number(num_str, 10)) return false;
        int num = atoi(num_str.c_str());

        string unit = s.substr(s.size() - 2);

        if(unit == "cm") return 150 <= num && num <= 193;
        if(unit == "in") return 59 <= num && num <= 76;
        return false;
    }

    bool check_hair_color_ok(const string& s){

        if(s.size() != 7) return false;
        if(s[0] != '#') return false;
        return is_number(s.substr(1), 16);
    }

    bool check_eye_color_ok(const string& s){
        unordered_set<string> color = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        return color.count(s);
    }

    bool check_pid_ok(const string& s){
        return s.size() == 9 && is_number(s, 10);
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test.txt");
    assert(input.is_open());

    string line, data = "";
    int res = 0;
    while(!input.eof()){
        getline(input, line);
        data += line;
        if(line == ""){
            res += Solution().is_valid(data);
            data = "";
        }
        else data += ' ';
    }
    res += Solution().is_valid(data);

    cout << res << endl;

    input.close();

    return 0;
}
