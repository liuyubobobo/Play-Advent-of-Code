/// Source : https://adventofcode.com/2020/day/13#part2
/// Author : liuyubobobo
/// Time   : 2020-12-14

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_set>

using namespace std;


class Solution{

public:
    long long solve(vector<int>& buses){

        vector<long long> a, m;
        for(int i = 0; i < buses.size(); i ++)
            if(buses[i] != -1) {
                m.push_back(buses[i]);
                a.push_back(buses[i] - i);
                while(a.back() < 0) a.back() += m.back();
                a.back() %= m.back();
            }
        for(int i = 0; i < a.size(); i ++)
            cout << "x mod " << m[i] << " = " << a[i] << endl;

        for(int i = 0; i < m.size(); i ++)
            for(int j = i + 1; j < m.size(); j ++)
                if(gcd(m[i], m[j]) > 1)
                    cout << "No co-prime!" << endl;

        return calSYDL(a, m);
    }

private:
    int gcd(int x, int y){

        if(x < y) swap(x, y);
        if(x % y == 0) return y;
        if(y == 0) return x;

        return gcd(y, x % y);
    }

    void exOJLD(long long a, long long b, long long &x, long long &y){
        //根据欧几里德定理
        if(b == 0ll){//任意数与0的最大公约数为其本身。
            x = 1ll;
            y = 0ll;
        }else{
            long long x1, y1;
            exOJLD(b, a%b, x1, y1);
            if(a * b < 0ll){//异号取反
                x = - y1;
                y = a / b * y1 - x1;
            }else{ //同号
                x = y1;
                y = x1 - a/b* y1;
            }
        }
    }

    //剩余定理
    long long calSYDL(vector<long long> a, vector<long long> m){

        int k = a.size();

        long long mm = 1ll;//最小公倍数
        long long result = 0;
        for(int i = 0; i < k; i++){
            mm *= m[i];
        }

        vector<long long> N(k);
        for(int j = 0; j < k; j++){
            long long L, J;
            exOJLD(mm/m[j], -m[j], L, J);
            assert(m[j] * J + 1ll == mm / m[j] * L);
            N[j] = m[j] * J + 1ll;
            result += N[j] * a[j];
        }
        return (result % mm + mm) % mm;//落在(0, mm)之间，这么写是为了防止result初始为负数，本例中不可能为负可以直接 写成：return result%mm;即可。
    }
};

int main() {

    ifstream input;
    input.open("../../input.txt");
//    input.open("../../input_test_1.txt"); // 1068781
    assert(input.is_open());

    int T;
    string line;
    input >> T >> line;

    vector<int> buses;
    for(int start = 0, i = start + 1; i <= line.size(); i ++)
        if(i == line.size() || line[i] == ','){

            string x = line.substr(start, i - start);
            if(x != "x"){
                int id = atoi(x.c_str());
                buses.push_back(id);
            }
            else
                buses.push_back(-1);

            start = i + 1;
            i = start;
        }
    cout << Solution().solve(buses) << endl;

    input.close();

    return 0;
}
