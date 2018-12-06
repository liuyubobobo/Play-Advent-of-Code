/// https://adventofcode.com/2018/day/3
/// liuyubobobo
/// 2018-12-05

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <unordered_set>

using namespace std;


class Solution{

private:
    class Claim{
    public:
        int id, left, top, w, h;
        Claim(int id, int left, int top, int w, int h):
            id(id), left(left), top(top), w(w), h(h){}
    };

public:
    int overlapped(const vector<string>& input){

        vector<Claim> claims;
        for(const string& s: input)
            claims.push_back(get_claim(s));

        int W = 0, H = 0;
        for(const Claim& claim: claims)
            W = max(W, claim.left + claim.w),
            H = max(H, claim.top + claim.h);

        vector<vector<unordered_set<int>>> canvas(H, vector<unordered_set<int>>(W));
        unordered_set<int> res;
        for(const Claim& claim: claims){
            bool intersection = false;
            for(int i = 0; i < claim.h; i ++)
                for(int j = 0; j < claim.w; j ++){
                    if(!canvas[i + claim.top][j + claim.left].empty()){
                        for(int x: canvas[i + claim.top][j + claim.left])
                            res.erase(x);
                        res.erase(claim.id);

                        intersection = true;
                    }
                    canvas[i + claim.top][j + claim.left].insert(claim.id);
                }
            if(!intersection)
                res.insert(claim.id);
        }
        assert(res.size() == 1);
        return *res.begin();
    }

private:
    Claim get_claim(const string& s){

        int at = s.find('@');
        int comma = s.find(',', at + 2);
        int colon = s.find(':', comma + 1);
        int x = s.find('x', colon + 1);

        int id = atoi(s.substr(1, at - 1 - 1).c_str());
        int a = atoi(s.substr(at + 2, comma - (at + 2)).c_str());
        int b = atoi(s.substr(comma + 1, colon - (comma + 1)).c_str());
        int c = atoi(s.substr(colon + 2, x - (colon + 2)).c_str());
        int d = atoi(s.substr(x + 1).c_str());
//        cout << s << endl;
//        cout << id << " " << a << " " << b << " " << c << " " << d << endl;
        return Claim(id, a, b, c, d);
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