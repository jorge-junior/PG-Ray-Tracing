#include "primitives.h"
#include "color.h"
#include "scene.h"

struct Sphere
{
    point3 center;
    float radius;
    Color color;
    const Color &intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene, point3 &outIntersectionPoint) const {};
};

struct Plane
{
    point3 origin;
    vec3 normal;
    Color color;
    const Color &intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene, point3 &outIntersectionPoint) const {};
};

struct Triangle
{
    point3 p1;
    point3 p2;
    point3 p3;
    vec3 normal;

    const point3 &operator[](int index) const {};
};

struct TriangleMesh
{
    int nTriangles;
    Triangle *triangles;
    Color color;
    const bool triangleIntersect(const point3 &rayOrigin, const vec3 &rayVec, const Triangle &t, point3 &outIntersectionPoint) const {};
    const Color &intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene, point3 &outIntersectionPoint) const {};
};