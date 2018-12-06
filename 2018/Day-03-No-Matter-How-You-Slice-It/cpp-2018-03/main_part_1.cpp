/// https://adventofcode.com/2018/day/3
/// liuyubobobo
/// 2018-12-05

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;


class Solution{

public:
    int overlapped(const vector<string>& input){

        vector<pair<pair<int, int>, pair<int, int>>> claims;
        for(const string& s: input)
            claims.push_back(get_claim(s));

        int W = 0, H = 0;
        for(const pair<pair<int, int>, pair<int, int>>& p: claims)
            W = max(W, p.first.first + p.second.first),
            H = max(H, p.first.second + p.second.second);

        vector<vector<int>> canvas(H, vector<int>(W, 0));
        for(const pair<pair<int, int>, pair<int, int>>& p: claims){
            int left = p.first.first, top = p.first.second,
                w = p.second.first, h = p.second.second;
            for(int i = 0; i < h; i ++)
                for(int j = 0; j < w; j ++)
                    canvas[i + top][j + left] ++;
        }

        int res = 0;
        for(int i = 0; i < H; i ++)
            for(int j = 0; j < W; j ++)
                res += (canvas[i][j] > 1);
        return res;
    }

private:
    pair<pair<int, int>, pair<int, int>> get_claim(const string& s){

//        cout << s << endl;
        int at = s.find('@');
        int comma = s.find(',', at + 2);
        int colon = s.find(':', comma + 1);
        int x = s.find('x', colon + 1);

        int a = atoi(s.substr(at + 2, comma - (at + 2)).c_str());
        int b = atoi(s.substr(comma + 1, colon - (comma + 1)).c_str());
        int c = atoi(s.substr(colon + 2, x - (colon + 2)).c_str());
        int d = atoi(s.substr(x + 1).c_str());
//        cout << a << " " << b << " " << c << " " << d << endl;
        return make_pair(make_pair(a, b), make_pair(c, d));
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    vector<string> claims;
    string s;
    while(!input.eof()){
        getline(input, s);
//        cout << s << endl;
        claims.push_back(s);
    }
    cout << Solution().overlapped(claims) << endl;

    input.close();

    return 0;
}