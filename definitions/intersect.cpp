#include "entities.h"

/*
    Intersections
*/

// all classes are currently defined in stubs (this will be solved when merging the implementation of th group)

const Color& Sphere::intersect(const point3& camOrigin, const Ray& rayVec, const Scene& scene) const {
    float a = vec3::dot(rayVec.direction, rayVec.direction);
    float b = 2.0f * (vec3::dot(rayVec.origin, rayVec.direction) + vec3::dot(rayVec.direction, this->center));
    float c = vec3::dot(rayVec.origin, rayVec.origin) + 2.0f * vec3::dot(rayVec.origin, this->center) + vec3::dot(this->center, this->center) - this->radius;
    float delta = b * b - 4.0f * a * c;

    if (delta >= 0.0f)
        return this->color;
    else
        return scene.backgroundColor;
};

const Color& Plane::intersect(const point3& camOrigin, const Ray& rayVec, const Scene& scene) const {};

const Color& TriangleMesh::intersect(const point3& camOrigin, const Ray& rayVec, const Scene& scene) const {};