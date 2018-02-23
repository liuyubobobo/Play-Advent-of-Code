/// http://adventofcode.com/2017/day/7
/// liuyubobobo
/// 2018-02-22

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution{

private:
    unordered_map<string, int> name_to_index;
    vector<string> index_to_name;
    unordered_map<int, int> weights;
    vector<int> sums;

    int max_index = 0;

    unordered_map<int, vector<int>> g;

public:
    int changed_weight(const vector<string>& info){

        create_g(info);
        int root_id = get_root_id();

        get_sums(root_id);
        assert(!equal(root_id));
        return solve(root_id);
    }

private:
    int solve(int node_id){

        if(g[node_id].size() == 2) {
            assert(equal(g[node_id][0]) && equal(g[node_id][1]));
            if(!equal(g[node_id][0]))
                return solve(g[node_id][0]);
            else
                return solve(g[node_id][1]);
        }

        assert(g[node_id].size() != 2);
        if(g[node_id].size() == 0)
            return 0;

        unordered_map<int, int> freq;
        for(int next: g[node_id])
            freq[sums[next]] += 1;
        if(freq.size() == 1)
            return 0;

        assert(freq.size() == 2);
        int minority_num = -1;
        int majority_num = -1;
        for(const pair<int, int>& p: freq)
            if(p.second == 1){
                assert(minority_num == -1);
                minority_num = p.first;
            }
            else{
                assert(majority_num == -1);
                majority_num = p.first;
            }
        assert(minority_num != -1 && majority_num != -1);

        int next_id = -1;
        for(int next: g[node_id])
            if(sums[next] == minority_num){
                assert(next_id == -1);
                next_id = next;
            }
        assert(next_id != -1);

        if(equal(next_id)) {
            if (g[next_id].size())
                return majority_num - g[next_id].size() * sums[g[next_id][0]];
            else
                return majority_num;
        }

        return solve(next_id);

    }

    bool equal(int node_id){

        if(g[node_id].size() == 0)
            return true;

        for(int next: g[node_id])
            if(sums[next] != sums[g[node_id][0]])
                return false;

        return true;
    }

    void get_sums(int root_id){

        sums.clear();
        for(int i = 0 ; i < index_to_name.size() ; i ++)
            sums.push_back(0);

        _get_sums(root_id);
    }

    int _get_sums(int node_id){

        assert(sums[node_id] == 0);

        sums[node_id] += weights[node_id];
        for(int next: g[node_id])
            sums[node_id] += _get_sums(next);

        return sums[node_id];
    }

    void create_g(const vector<string>& info){

        name_to_index.clear();
        index_to_name.clear();
        max_index = 0;
        g.clear();

        for(const string& line: info){
            stringstream ss(line);
            string name, weight_s;
            ss >> name >> weight_s;
            //cout << name << " " << weight_s << " ";

            int root_id = get_id(name);
            weights[root_id] = stoi(weight_s.substr(1, weight_s.size()-2));

            string arrow;
            if(ss >> arrow){
                //cout << arrow << " ";

                string sub;
                while(ss >> sub){
                    //cout << sub << " ";
                    if(sub[sub.size()-1] == ',')
                        sub = sub.substr(0, sub.size()-1);

                    int sub_id = get_id(sub);
                    g[root_id].push_back(sub_id);
                }
                //cout << endl;
            }
        }
    }

    int get_id(const string& name){

        if(name_to_index.find(name) != name_to_index.end())
            return name_to_index.find(name)->second;

        name_to_index[name] = max_index;
        index_to_name.push_back(name);
        max_index ++;

        return name_to_index[name];
    }

    int get_root_id(){

        vector<int> indegrees(index_to_name.size(), 0);
        for(const pair<int, vector<int>>& p: g){
            if(p.second.size()){
                //cout << p.second.size() << endl;
                for(int v: p.second)
                    indegrees[v] ++;
            }
        }

        int root_id = -1;
        for(int i = 0; i < indegrees.size() ; i ++)
            if(indegrees[i] == 0){
                assert(root_id == -1);
                root_id = i;
            }
        return root_id;
    }
};


int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<string> info;
    string line;
    while(!input.eof()){
        getline(input, line);
        info.push_back(line);
    }

    cout << Solution().changed_weight(info) << endl;

    input.close();

    return 0;
}