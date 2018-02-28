/// http://adventofcode.com/2017/day/23
/// liuyubobobo
/// 2018-02-27

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

// The program is to calculate how many non-prime numbers
// between range(109300, 126300, 17)
class Solution{

public:
    int left_in_h(){

        int res = 0;
        for(int i = 109300; i <= 126300; i += 17)
            if(!is_prime(i))
                res ++;

        return res;
    }

private:
    bool is_prime(int num){
        if(num % 2 == 0)
            return false;

        for(int i = 3 ; i*i <= num ; i += 2)
            if(num % i == 0)
                return false;

        return true;
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<string> instructions;
    string line;
    while(!input.eof()) {
        getline(input, line);
        // cout << line << endl;
        instructions.push_back(line);
    }

    cout << Solution().left_in_h() << endl;

    input.close();

    return 0;
}