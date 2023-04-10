#ifndef Camera_h
#define Camera_h

#include "math.h"
#include <iostream>
#include "Vetor.cpp"

using namespace std;

struct Camera 
{
    int C[3]; 
    int M[3];
    Vec3 Vup;
    Vec3 W; // mesma direcao que (M − C), mas sentido oposto;
    Vec3 V; // o ponto da mira
    Vec3 U; // o ponto da localizacao da camera,
    float d; // Direção da camera
    float altura;
    float largura;

    Camera();
    Camera(const int &C, const int &M,
            const Vec3 &Vup, const Vec3 &W,
            const Vec3 &V, const Vec3 &U,
            float d, float altura, float largura);
    
    virtual ~Camera();
}

#endif