/// Source : https://adventofcode.com/2020/day/5#part2
/// Author : liuyubobobo
/// Time   : 2020-12-05

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_set>

using namespace std;


class Plane{

private:
    unordered_set<int> seats;

public:
    Plane(){}

    int add(const string& s){

        int rowl = 0, rowr = 127;
        for(int i = 0; i < 7; i ++){
            int mid = (rowl + rowr) / 2;
            if(s[i] == 'B') rowl = mid + 1;
            else rowr = mid;
        }
        assert(rowl == rowr);

        int coll = 0, colr = 7;
        for(int i = 7; i < 10; i ++){
            int mid = (coll + colr) / 2;
            if(s[i] == 'R') coll = mid + 1;
            else colr = mid;
        }
        assert(coll == colr);

        seats.insert(rowl * 8 + coll);
    }

    int missing(){

        int start = 0;
        for(;; start ++)
            if(seats.count(start)) break;

        for(int i = start + 1;;i ++)
            if(!seats.count(i)) return i;
        return -1;
    };
};

int main() {

    ifstream input;
    input.open("../../input.txt");
    assert(input.is_open());

    string line;
    Plane plane;
    while(!input.eof()){
        input >> line;
        plane.add(line);
    }
    cout << plane.missing() << endl;

    input.close();

    return 0;
}
