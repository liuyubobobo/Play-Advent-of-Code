/// Source : https://adventofcode.com/2020/day/20
/// Author : liuyubobobo
/// Time   : 2020-12-23

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;


class Piece{

public:
    const static int S = 10;

public:
    int id;
    vector<string> g;

    Piece(int id, const vector<string>& g): id(id), g(g){
        assert(g.size() == S);
        for(const string& s: g) assert(s.size() == S);
    }

    void rotate(){

        vector<string> g2(S, string(S, ' '));
        for(int i = 0; i < S; i ++)
            for(int j = 0; j < S; j ++)
                g2[j][S - 1 - i] = g[i][j];
        g = g2;

//        for(const string& s: g)
//            for(char c: s) assert(c != ' ');
    }

    void flipV(){
        for(string& s: g)
            reverse(s.begin(), s.end());
    }

    void flipH(){

        for(int col = 0; col < S; col ++){
            int i = 0, j = S - 1;
            while(i < j){
                swap(g[i][col], g[j][col]);
                i ++; j --;
            }
        }
    }

    void flipD(){

        flipV();
        flipH();
    }
};

class Solution{

private:
    int side;

public:
    long long solve(vector<Piece>& pieces){

        side = sqrt(pieces.size());
        assert(side * side == pieces.size());

        vector<vector<int>> res(side, vector<int>(side, 0));
        vector<bool> used(pieces.size(), false);
        bool tag = dfs(pieces, 0, 0, used, res);

        for(const vector<int>& row: res){
            for(int e: row) cout << e << '\t';
            cout << endl;
        }
        assert(tag);
        return (long long)pieces[res[0][0]].id * pieces[res[0].back()].id * pieces[res.back()[0]].id * pieces[res.back().back()].id;
    }

private:
    bool dfs(vector<Piece>& pieces, int x, int y,
             vector<bool>& used, vector<vector<int>>& res){

//        cout << x << " " << y << endl;
        if(x == side) return true;
        if(y == side) return dfs(pieces, x + 1, 0, used, res);

        for(int i = 0; i < pieces.size(); i ++)
            if(!used[i]){

                for(int r = 0; r < 4; r ++){
                    if(ok(pieces, res, i, x, y)) {
                        used[i] = true;
                        res[x][y] = i;
                        if (dfs(pieces, x, y + 1, used, res)) return true;
                        used[i] = false;
                        res[x][y] = -1;
                    }

                    if(r < 2) {
                        pieces[i].flipV();
                        if (ok(pieces, res, i, x, y)) {
                            used[i] = true;
                            res[x][y] = i;
                            if (dfs(pieces, x, y + 1, used, res)) return true;
                            used[i] = false;
                            res[x][y] = -1;
                        }
                        pieces[i].flipV();

                        pieces[i].flipH();
                        if (ok(pieces, res, i, x, y)) {
                            used[i] = true;
                            res[x][y] = i;
                            if (dfs(pieces, x, y + 1, used, res)) return true;
                            used[i] = false;
                            res[x][y] = -1;
                        }
                        pieces[i].flipH();
                    }

                    pieces[i].rotate();
                }
            }
        return false;
    }

    bool ok(const vector<Piece>& pieces, vector<vector<int>>& res, int index, int x, int y){

        if(x - 1 >= 0){
            if(!ok(pieces[res[x - 1][y]], pieces[index], 0)) return false;
        }

        if(y - 1 >= 0){
            if(!ok(pieces[res[x][y - 1]], pieces[index], 1)) return false;
        }

        return true;
    }

    bool ok(const Piece& p1, const Piece& p2, int type){

        string a = "", b = "";
        if(type == 0){
            a = p1.g.back();
            b = p2.g[0];
        }
        else{
            for(const string& s: p1.g) a += s.back();
            for(const string& s: p2.g) b += s[0];
        }

        assert(a.size() == b.size() && a.size() == Piece::S);
//        cout << a << " " << b << endl;
        return a == b;
    }

};

int main() {

    ifstream input;
//    input.open("../../input_test_1.txt"); // 20899048083289
    input.open("../../input.txt");
    assert(input.is_open());

    string line;
    vector<Piece> v;
    while(!input.eof()){
        getline(input, line);
        int cindex = line.find(':');
        assert(cindex != string::npos);
        int id = atoi(line.substr(5, cindex - 5).c_str());

        vector<string> g;
        while(true){
            getline(input, line);
            if(line == "") break;
            g.push_back(line);
        }
        assert(g.size() == Piece::S);
        v.push_back(Piece(id, g));
    }

    cout << Solution().solve(v) << endl;

    input.close();

    return 0;
}
