#ifndef Normal_h
#define Normal_h

#include <iostream>
#include "math.h"

using namespace std;

class Ponto;
class Vec3;

class Normal {
public:
    float x;
    float y;
    float z;
    
    Normal();
    
    Normal(float x, float y, float z);
    
    Normal(Normal const &n);
    
    Normal(Ponto const& p);
    
    Normal(Vec3 const& v);
    
    ~Normal();
    Normal& operator= (Normal const& n);
    
    float comp();
    
    Normal normalizar();
    
    Normal neg() const;

    
    void print()
    {
        cout << x << '/' << y << '/' << z<< endl;
    }
};

float pr_escn(Normal n1, Normal n2);
    
Normal pr_vetn(Normal n1, Normal n2);

inline Normal operator + (const Normal & n1, const Normal &n2) {
    return Normal(n1.x + n2.x, n1.y + n2.y, n1.z + n2.z);
}

inline Normal operator - (const Normal & n1, const Normal &n2){
    return Normal(n1.x - n2.x, n1.y - n2.y, n1.z - n2.z);
}

inline Normal operator * (const Normal & n1, const Normal &n2){
    return Normal(n1.x * n2.x, n1.y * n2.y,n1.z * n2.z);
}

inline Normal operator / (const Normal & n1, float const& f) {
    return Normal(n1.x / f, n1.y / f,n1.z / f);
}


inline Normal operator * (const Normal & n1, float const& f) {
    return Normal(n1.x * f, n1.y * f,n1.z * f);
}


#endif