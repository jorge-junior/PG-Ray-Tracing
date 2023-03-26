#include "entities.h"

/*
    Intersections
*/

// all classes are currently defined in stubs (this will be solved when merging the implementation of the group)

const Color &Sphere::intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene) const
{
    float a = vec3::dot(rayVec.direction, rayVec.direction);
    float b = 2.0f * (vec3::dot(camOrigin, rayVec.direction) + vec3::dot(rayVec.direction, this->center));
    float c = vec3::dot(camOrigin, camOrigin) + 2.0f * vec3::dot(camOrigin, this->center) + vec3::dot(this->center, this->center) - this->radius;
    float delta = b * b - 4.0f * a * c;

    if (delta >= 0.0f)
        return this->color;
    else
        return scene.backgroundColor;

    // point of intersection:
    // float t1 = -b * delta / 2a;
    // float t = t1;
    // if (delta > 0)
    // {
    //     float t2 = -b * -delta / 2a;
    //     t = (t1 < t2) ? t1 : t2;
    // }
    // else if (delta < 0)
    // {
    //     return NULL;
    // }
    // return camOrigin + rayVec * t;
};

const Color &Plane::intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene) const
{
    float a = vec3::dot(rayVec.direction, this->normal);
    if (a == 0)
        return scene.backgroundColor;
    else
        return this->color;

    // point of intersection:
    // float b = vec3::dot(camOrigin, this->normal) - vec3::dot(this->origin, this->normal);
    // float t = -b / a;
    // return camOrigin + rayVec * t;
};

const Color &TriangleMesh::intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene) const {};