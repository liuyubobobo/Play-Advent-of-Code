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
    int stay_closest(const vector<Particle>& particles){

        double t = 1e5;
        int res = -1;
        double min_dis = numeric_limits<double>::max();
        for(const Particle& particle: particles){

            double p1 = particle.p.x + particle.a.x / 2.0 * t * t + (particle.a.x / 2.0 + particle.v.x) * t;
            double p2 = particle.p.y + particle.a.y / 2.0 * t * t + (particle.a.y / 2.0 + particle.v.y) * t;
            double p3 = particle.p.z + particle.a.z / 2.0 * t * t + (particle.a.z / 2.0 + particle.v.z) * t;

            double dis = square_sum(p1, p2, p3);
            if(dis < min_dis){
                min_dis = dis;
                res = particle.id;
            }
        }

        return res;
    }

private:
    double square_sum(double x, double y, double z){
        return sqrt(x * x + y * y + z * z);
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