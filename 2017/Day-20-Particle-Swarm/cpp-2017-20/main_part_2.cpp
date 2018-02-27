/// http://adventofcode.com/2017/day/20
/// liuyubobobo
/// 2018-02-26

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>
#include <unordered_set>
#include <unordered_map>

using namespace std;


struct Point{
    int x, y, z;

    Point(){
        this->x = this->y = this->z = 0;
    }

    Point(int x, int y, int z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point& operator+=(const Point& rhs){
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }

    string point_string(){
        return to_string(this->x) + "#" + to_string(this->y) + "#" + to_string(this->z);
    }
};

struct Particle{

    int id;
    Point p, v, a;

    Particle(const Point& p, const Point& v, const Point& a, int id){
        this->id = id;
        this->p = p;
        this->v = v;
        this->a = a;
    };
};

class Solution{

public:
    int stay_closest(vector<Particle>& particles){

        unordered_set<int> left_particles;
        for(int i = 0; i < particles.size() ; i ++)
            left_particles.insert(i);

        int max_t = 1000;
        unordered_map<string, vector<int>> pos;
        for(int t = 0 ; t <= max_t; t ++){
            pos.clear();
            for(int index: left_particles){
                particles[index].v += particles[index].a;
                particles[index].p += particles[index].v;
                pos[particles[index].p.point_string()].push_back(index);
            }

            for(const pair<string, vector<int>>& p: pos)
                if(p.second.size() >= 2)
                    for(int index: p.second)
                        left_particles.erase(index);
        }

        return left_particles.size();
    }
};


void get_nums(const string& line, int& a, int& b, int& c){

    int left = line.find('<');
    int right = line.find('>');
    // cout << line << " left = " << left << " right = " << right << endl;
    assert(left != string::npos);
    assert(right != string::npos);
    assert(left < right);

    string nums_str = line.substr(left + 1, right - left - 1);
    // cout << nums_str << endl;
    for(int i = 0 ; i < nums_str.size(); i ++)
        if(nums_str[i] == ',')
            nums_str[i] = ' ';

    // cout << nums_str << endl;
    stringstream ss(nums_str);
    ss >> a >> b >> c;
}

Particle get_particle(const string& line, int id){

    stringstream ss(line);
    string pline;
    int x, y, z;

    ss >> pline;
    get_nums(pline, x, y, z);
    Point p(x, y, z);
    // cout << x << " " << y << " " << z << endl;

    ss >> pline;
    get_nums(pline, x, y, z);
    Point v(x, y, z);
    // cout << x << " " << y << " " << z << endl;

    ss >> pline;
    get_nums(pline, x, y, z);
    Point a(x, y, z);
    // cout << x << " " << y << " " << z << endl;

    return Particle(p, v, a, id);
}

int main() {

    ifstream input;
    input.open("../input.txt");
    assert(input.is_open());

    vector<Particle> particles;
    string line;
    int id = 0;
    while(!input.eof()) {

        getline(input, line);
        particles.push_back(get_particle(line, id));
        id ++;
    }

    cout << Solution().stay_closest(particles) << endl;

    input.close();

    return 0;
}