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
    int get_message(const vector<string>& rooms, string target){

        int res = 0;
        for(const string& line: rooms){
            int sectorID = check(line, target);
            if(sectorID != -1)
                return sectorID;
        }
        return -1;
    }

private:
    int check(const string& line, const string& target){

        int first_digit = 0;
        for(; !isdigit(line[first_digit]); first_digit ++);
        assert(first_digit - 1 >= 0 && line[first_digit - 1] == '-');

        int left = first_digit;
        for(; line[left] != '[' ; left ++);
        assert(left + 1 < line.size() && isalpha(line[left + 1]));
        assert(line.substr(left + 1).size() == 6);
        assert(line[line.size() - 1] == ']');

        string s = line.substr(0, first_digit - 1);
        int sectorID = stoi(line.substr(first_digit, left - first_digit));

        for(int i = 0 ; i < s.size() ; i ++)
            if(s[i] == '-')
                s[i] = ' ';
            else
                s[i] = ('a' + (s[i] - 'a' + sectorID) % 26);
        // cout << s << endl;

        return s == target ? sectorID : -1;
    }

    static bool cmp(const pair<int, char>& p1, const pair<int, char>& p2){
        if(p1.first != p2.first)
            return p1.first > p2.first;
        return p1.second < p2.second;
    }
};

int main() {

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

    cout << Solution().get_message(rooms, "northpole object storage") << endl;

    input.close();

    return 0;
}