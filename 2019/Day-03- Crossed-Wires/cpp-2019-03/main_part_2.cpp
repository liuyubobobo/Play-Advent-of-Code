/// Source : https://adventofcode.com/2019/day/3#part2
/// Author : liuyubobobo
/// Time   : 2020-12-03

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <map>
#include <unordered_map>

using namespace std;


class Solution{

public:
    int solve(const string& s1, const string& s2){

        map<pair<int, int>, int> map1 = go(s1);
        map<pair<int, int>, int> map2 = go(s2);

        int res = INT_MAX;
        for(const pair<pair<int, int>, int>& p: map2)
            if(map1.count(p.first)){
                int d = map1[p.first] + map2[p.first];
                if(d && d < res) res = d;
            }
        return res;
    }

private:
    map<pair<int, int>, int> go(const string& s){

        unordered_map<char, int> dx = {{'R', 1}, {'L', -1}, {'U', 0}, {'D', 0}};
        unordered_map<char, int> dy = {{'R', 0}, {'L', 0}, {'U', 1}, {'D', -1}};

        map<pair<int, int>, int> res;
        int x = 0, y = 0;
        res[{x, y}] = 0;

        int a = 1;
        for(int start = 0, i = start + 1; i <= s.size(); i ++)
            if(i == s.size() || s[i] == ','){
                char d = s[start];
                int step = atoi(s.substr(start + 1, i - (start + 1)).c_str());
                for(int k = 0; k < step; k ++){
                    x += dx[d], y += dy[d];
                    res[{x, y}] = a ++;
                }

                start = i + 1;
                i = start;
            }
        return res;
    }
};

int main() {

    ifstream input;
//    input.open("../../input_test.txt");
    input.open("../../input.txt");
    assert(input.is_open());

    string s1, s2;
    input >> s1 >> s2;

    cout << Solution().solve(s1, s2) << endl;

    input.close();

    return 0;
}
