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
    int max_index = 0;

    unordered_map<int, vector<int>> g;

public:
    string root(const vector<string>& info){

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

        vector<int> indegrees(index_to_name.size(), 0);
        for(const pair<int, vector<int>>& p: g){
            if(p.second.size()){
                //cout << p.second.size() << endl;

                for(int v: p.second)
                    indegrees[v] ++;
            }
        }

        string res = "";
        for(int i = 0; i < indegrees.size() ; i ++)
            if(indegrees[i] == 0){
                assert(res == "");
                res = index_to_name[i];
            }

        return res;
    }

private:
    int get_id(const string& name){

        if(name_to_index.find(name) != name_to_index.end())
            return name_to_index.find(name)->second;

        name_to_index[name] = max_index;
        index_to_name.push_back(name);
        max_index ++;

        return name_to_index[name];
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

    cout << Solution().root(info) << endl;

    input.close();

    return 0;
}