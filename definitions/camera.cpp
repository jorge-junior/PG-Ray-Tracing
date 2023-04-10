#include <iostream>

#include "Camera.hpp"

Camera::Camera()
       : C(0.0f, 0.0f, 0.0f),
         M(),
         Vup(),
         W(),
         V(),
         U(),
         d(),
         altura(),
         largura()
{
}

Camera::Camera(const int &C, const int &M,
            const Vec3 &Vup, const Vec3 &W,
            const Vec3 &V, const Vec3 &U,
            float d, float altura, float largura)
       : C(C),
         M(M),
         Vup(Vup),
         W(W),
         V(V),
         U(U),
         d(d),
         altura(altura),
         largura(largura)
{
}

Camera::~Camera() {}


         
        