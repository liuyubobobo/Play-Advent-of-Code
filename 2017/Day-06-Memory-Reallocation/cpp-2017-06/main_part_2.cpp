/// http://adventofcode.com/2017/day/6
/// liuyubobobo
/// 2018-02-22

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <unordered_map>

using namespace std;


void print_vec(const vector<int>& vec){
    for(int num: vec)
        cout << num << " ";
    cout << endl;
}

class Solution{

public:
    int cycle_num(vector<int>& memories){

        int res = 0;
        unordered_map<string, int> seen;
        seen[vector_to_string(memories)] = 0;
        // print_vec(memories);

        while(true){

            int relloc_index = get_max_index(memories);
            int blocks = memories[relloc_index];
            memories[relloc_index] = 0;

            for(int i = 1 ; i <= 16 ; i ++){
                memories[(relloc_index + i) % 16] += blocks / 16;
                if(i <= blocks % 16)
                    memories[(relloc_index + i) % 16] += 1;
            }

            res ++;
            // print_vec(memories);

            string id = vector_to_string(memories);
            if(seen.find(id) != seen.end()){
                return res - seen.find(id)->second;
            }

            seen[id] = res;
        }

        assert(false);
    }

private:
    string vector_to_string(const vector<int>& vec){
        string res = "";
        for(int num: vec)
            res += to_string(num) + "#";
        return res;
    }

    int get_max_index(const vector<int>& vec){
        int res = 0;
        for(int i = 1 ; i < vec.size() ; i ++)
            if(vec[i] > vec[res])
                res = i;
        return res;
    }
};

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<int> memories;
    for(int i = 0 ; i < 16 ; i ++){
        int num;
        input >> num;
        memories.push_back(num);
    }
    assert(memories.size() == 16);

    // print_vec(memories);

    cout << Solution().cycle_num(memories) << endl;

    input.close();

    return 0;
}