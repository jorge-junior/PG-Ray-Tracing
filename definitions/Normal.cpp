#include <iostream>

#include "Normal.hpp"
#include "Vetor.hpp"

using namespace std;

Normal::Normal():x(0),y(0),z(0){}

Normal::Normal(float x, float y, float z):x(x),y(y),z(z){}

Normal::Normal(Normal const &n):x(n.x),y(n.y),z(n.z){}

Normal::Normal(Ponto const& p):x(p.x),y(p.y),z(p.z){}

Normal::Normal(Vec3 const& v):x(v.x),y(v.y),z(v.z){}


Normal::~Normal(){}
Normal& Normal::operator= (Normal const& n){
    x = n.x; y = n.y; z=n.z;
    return(*this);
}

float Normal::comp() {
    return (sqrt (qdd(x) + qdd(y) + qdd(z)));
}

Normal Normal::normalizar() {
    float mag = comp(); //magnitude do vetor
    return Normal(x /mag, y / mag, z /mag);
}

Normal Normal::neg() const{
    return Normal(-x,-y,-z);
}

float pr_escn(Normal n1, Normal n2) {
    return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

Normal pr_vetn(Normal n1, Normal n2) {
    return Normal(n1.y * n2.z - n1.z * n2.y,
		n1.z * n2.x - n1.x * n2.z,
		n1.x * n2.y - n1.y * n2.x);
}