#include "vec3.h"
#include "point3.h"
#include "color.h"
#include "scene.h"
#include <iostream>

struct Sphere
{
    point3 center;
    float radius;
    Color color;
    const Color &intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene) const {};
};

struct Plane
{
    point3 origin;
    vec3 normal;
    Color color;
    const Color &intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene) const {};
};

struct TriangleMesh
{
    const Color &intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene) const {};
};