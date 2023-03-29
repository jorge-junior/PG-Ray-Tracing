#include "vec3.h"
#include "point3.h"
#include "color.h"
#include "scene.h"

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

struct Triangle
{
    point3 p1;
    point3 p2;
    point3 p3;
    vec3 normal;
};

struct TriangleMesh
{
    int nTriangles;
    Triangle* triangles;
    Color color;
    const bool triangleIntersect(const vec3 &rayVec, const Triangle &triangle) const {};
    const Color &intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene) const {};
};