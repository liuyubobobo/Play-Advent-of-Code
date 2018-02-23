/// http://adventofcode.com/2017/day/10
/// liuyubobobo
/// 2018-02-23

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>

using namespace std;


class Solution{

public:
    string hash(const string& line){

        vector<int> lengths = get_lengths(line);

        vector<int> numbers(256, 0);
        for(int i = 0 ; i < 256 ; i ++)
            numbers[i] = i;

        int cur = 0;
        int skip = 0;
        for(int round = 0 ; round < 64 ; round ++)
            for(int length: lengths){

                vector<int> tvec;
                for(int i = 0; i < length; i ++)
                    tvec.push_back(numbers[(cur + i) % 256]);
                reverse(tvec.begin(), tvec.end());

                for(int i = 0; i < length; i ++)
                    numbers[(cur + i) % 256] = tvec[i];

                cur = (cur + length + skip) % 256;
                skip = (skip + 1) % 256;
            }

        vector<int> dense_hash;
        for(int i = 0 ; i < 16 ; i ++){
            int res = numbers[i*16];
            for(int j = 1 ; j < 16 ; j ++)
                res ^= numbers[i*16+j];
            dense_hash.push_back(res);
        }

        stringstream ss("");
        for(int num: dense_hash)
            ss << std::hex << setw(2) << setfill('0') << num;

        return ss.str();
    }

private:
    vector<int> get_lengths(const string& line){

        vector<int> lengths;
        for(char c: line)
            lengths.push_back((int)c);

        vector<int> others = {17, 31, 73, 47, 23};
        for(int length: others)
            lengths.push_back(length);

        return lengths;
    }
};


int main() {

//    cout << Solution().hash("") << endl;
//    cout << (Solution().hash("") == "a2582a3a0e66e6e86e3812dcb672a272") << endl;
//
//    cout << Solution().hash("AoC 2017") << endl;
//    cout << (Solution().hash("AoC 2017") == "33efeb34ea91902bb2f59c9920caa6cd") << endl;
//
//    cout << Solution().hash("1,2,3") << endl;
//    cout << (Solution().hash("1,2,3") == "3efbe78a8d82f29979031a4aa0b16a9d") << endl;
//
//    cout << Solution().hash("1,2,4") << endl;
//    cout << (Solution().hash("1,2,4") == "63960835bcdc130f0b66d7ff4f6a5a8e") << endl;

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    string line;
    if(!input.eof())
        getline(input, line);

    cout << Solution().hash(line) << endl;

    input.close();

    return 0;
}