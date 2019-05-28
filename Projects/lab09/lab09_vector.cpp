#include "lab09_vector.h"
#include<string>
using std::string; using std::to_string;
MathVector::MathVector(long a,long b) {
    x = a;
    y = b;
}

MathVector MathVector::add(const MathVector &m) {
    MathVector n(this->x+m.x,this->y+m.y);
    return n;
}

MathVector MathVector::mult(long a) {
    MathVector n(this->x*a, this->y*a);
    return n;
}

long MathVector::mult(const MathVector &m) {
    long dot = ((this->x*m.x) + (this->y*m.y));
    return dot;
}

double MathVector::magnitude() {
    double mag = sqrt(pow(this->x,2)+pow(this->y,2));
    return mag;
}

string vec_to_str(const MathVector&v) {
    string ret; 
    string x = to_string(v.x);
    string y = to_string(v.y);
    ret = {x + ':' + y};
    return ret;

    
}
