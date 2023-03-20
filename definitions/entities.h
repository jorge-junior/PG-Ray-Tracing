#include "vec3.h"
#include "point3.h"
#include "color.h"
#include "scene.h"
#include <iostream>


struct Ray{
    point3 origin;
    vec3 direction;
};

struct Sphere{
    point3 center;
    float radius;
    Color color;
    const Color& intersect(const point3& camOrigin, const Ray& rayVec, const Scene& scene) const {};
};

struct Plane{
    Color color;
    const Color& intersect(const point3& camOrigin, const Ray& rayVec, const Scene& scene) const {};
};

struct TriangleMesh{
    const Color& intersect(const point3& camOrigin, const Ray& rayVec, const Scene& scene) const {};
};