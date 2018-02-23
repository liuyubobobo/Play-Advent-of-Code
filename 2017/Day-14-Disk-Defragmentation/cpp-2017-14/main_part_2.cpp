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

private:
    vector<vector<bool>> disk;
    vector<vector<bool>> visited;
    const int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

public:

    int region_num(const string& key){

        disk.clear();
        visited.clear();
        for(int i = 0 ; i < 128 ; i ++){
            disk.push_back(vector<bool>(128, false));
            visited.push_back(vector<bool>(128, false));
        }

        get_disk(key);
        //print_8_8();

        int res = 0;
        for(int i = 0 ; i < 128 ; i ++)
            for(int j = 0 ; j < 128 ; j ++)
                if(disk[i][j] && !visited[i][j]){
                    dfs(i, j);
                    res ++;
                    //print_8_8();
                }
        return res;
    }

private:
    void dfs(int x, int y){

        visited[x][y] = true;
        for(int i = 0 ; i < 4 ; i ++){
            int newX = x + d[i][0];
            int newY = y + d[i][1];
            if(inArea(newX, newY) && disk[newX][newY] && !visited[newX][newY])
                dfs(newX, newY);
        }
    }

    bool inArea(int x, int y){
        return x >= 0 && x < 128 && y >= 0 && y < 128;
    }

    void get_disk(const string& key){

        for(int i = 0 ; i < 128 ; i ++){
            vector<int> hashcode = hash(key + "-" + to_string(i));
            assert(hashcode.size() == 16);
            for(int j = 0; j < 16; j ++){
                int num = hashcode[j];
                //cout << num << endl;
                for(int k = 0; k < 8 ; k ++){
                    disk[i][8 * j + 7 - k] = ((num&1) != 0 ? true : false);
                    num >>= 1;
                    visited[i][8 * j + 7 - k] = false;
                }
                assert(num == 0);
            }
        }

        return;
    }

    vector<int> hash(const string& line){

        vector<int> lengths = get_lengths(line);

        vector<int> numbers;
        for(int i = 0 ; i < 256 ; i ++)
            numbers.push_back(i);

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

    void print_8_8(){

        for(int i = 0 ; i < 8 ; i ++){
            for(int j = 0 ; j < 8 ; j ++)
                cout << (disk[i][j] ? 1 : 0);
            cout << endl;
        }
        cout << endl;
    }
};

int main() {

    cout << Solution().region_num("flqrgnkx") << endl;
    cout << Solution().region_num("stpzcrnm") << endl;

    return 0;
}