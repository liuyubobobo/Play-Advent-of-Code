#include <iostream>

using namespace std;


class Solution{

private:
    int factorA = 16807, factorB = 48271;
    int turns = 40000000;
    long long mod = 2147483647;
    int mask = (1 << 16) - 1;

public:
    int count(int startA, int startB){

        int res = 0;
        int cur_a = startA, cur_b = startB;
        for(int i = 0; i < turns; i ++){
            cur_a = (int)(((long long)cur_a * (long long)factorA) % mod);
            cur_b = (int)(((long long)cur_b * (long long)factorB) % mod);

            if((cur_a & mask) == (cur_b & mask))
                res ++;
        }
        return res;
    }
};

int main() {

    cout << Solution().count(65, 8921) << endl;
    cout << Solution().count(679, 771) << endl;

    return 0;
}