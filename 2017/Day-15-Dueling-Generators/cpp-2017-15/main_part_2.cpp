#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


class Solution{

private:
    int factorA = 16807, factorB = 48271;
    int turns = 5000000;
    long long mod = 2147483647;
    int mask = (1 << 16) - 1;

public:
    int count(int startA, int startB){

        int cur_a = startA, cur_b = startB;
        vector<int> vec_a, vec_b;
        for(int i = 0; ; i ++){
            cur_a = (int)(((long long)cur_a * (long long)factorA) % mod);
            cur_b = (int)(((long long)cur_b * (long long)factorB) % mod);

            if(cur_a % 4 == 0)
                vec_a.push_back(cur_a);

            if(cur_b % 8 == 0)
                vec_b.push_back(cur_b);

            if(vec_a.size() >= turns && vec_b.size() >= turns)
                break;
        }

        int res = 0;
        int length = min(vec_a.size(), vec_b.size());
        assert(length == turns);
        for(int i = 0 ; i < length; i ++)
            if((vec_a[i] & mask) == (vec_b[i] & mask))
                res ++;
        return res;
    }
};

int main() {

    cout << Solution().count(65, 8921) << endl;
    cout << Solution().count(679, 771) << endl;

    return 0;
}