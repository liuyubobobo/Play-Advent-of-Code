/// http://adventofcode.com/2017/day/14
/// liuyubobobo
/// 2018-02-23

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cassert>

using namespace std;


class Solution{

public:
    int used(const string& key){

        int res = 0;
        for(int i = 0 ; i < 128 ; i ++){
            vector<int> hashcode = hash(key + "-" + to_string(i));
            assert(hashcode.size() == 16);
            for(int num: hashcode)
                for(int j = 0; j < 8 ; j ++){
                    res += (num&1);
                    num >>= 1;
                }
        }

        return res;
    }

private:
    vector<int> hash(const string& line){

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

        return dense_hash;
    }

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

    cout << Solution().used("flqrgnkx") << endl;
    cout << Solution().used("stpzcrnm") << endl;

    return 0;
}