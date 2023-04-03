#include "entities.h"
#include <cmath>

/*
    Intersections
*/

// all classes are currently defined in stubs (this will be solved when merging the implementation of the group)

const Color &Sphere::intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene, float &t) const
{
    /* Calculate the intersection point of a ray with a sphere. Returns the color of the sphere if intersected */

    // calculate discriminant

    float a = vec3::dot(rayVec, rayVec);
    float b = 2.0f * vec3::dot((camOrigin + this->center), rayVec);
    float c = vec3::dot(camOrigin, this->center) * vec3::dot(camOrigin, this->center) - this->radius * this->radius;
    float delta = b * b - 4.0f * a * c;

    if (delta < 0.0f) // no intersection
        return scene.backgroundColor;

    // intersection point

    float t0 = (-b - sqrt(delta)) / (2 * a);
    float t1 = (-b + sqrt(delta)) / (2 * a);
    float _t = (t0 < t1) ? t0 : t1;

    if (_t < 1)
        t = _t;

    return this->color;
};

const Color &Plane::intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene, float &t) const
{
    /* Calculate the intersection point of a ray with a plane. Returns the color of the plane if intersected */

    const float EPSILON = 0.0000001;

    // check if ray is parallel

    float a = vec3::dot(rayVec, this->normal);
    if (a > -EPSILON && a < EPSILON)
        return scene.backgroundColor; // ray is parallel

    // calculate intersection point

    float _t = vec3::dot((this->origin - camOrigin), normal) / a;
    if (_t > EPSILON) // intersect
    {
        t = _t;
        return this->color;
    }
    return scene.backgroundColor; // no intersection
};

const bool Triangle::intersect(const point3 &rayOrigin, const vec3 &rayVec, float &t) const
{
    /* Uses Moller-Trumbore intersection algorithm to chek intersection of a ray with a triangle */

    const float EPSILON = 0.0000001;

    // triangle edge vectors

    vec3 edge1 = this->p2 - this->p1;
    vec3 edge2 = this->p3 - this->p1;
    vec3 h = vec3::cross(rayVec, edge2);

    // check if ray is parallel

    float a = vec3::dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return false; // ray is parallel

    // find beta coordinate

    float f = 1.0 / a;
    vec3 s = rayOrigin - this->p1;
    float beta = f * vec3::dot(s, h);
    if (beta < 0.0 || beta > 1.0)
        return false; // outside triangle

    // find gamma coordinate

    vec3 q = vec3::cross(s, edge1);
    float gamma = f * vec3::dot(rayVec, q);
    if (gamma < 0.0 || beta + gamma > 1.0)
        return false; // outside triangle

    // find the intersection point

    float _t = f * vec3::dot(edge2, q);
    if (_t > EPSILON) // point intersection
    {
        t = _t;
        return true;
    }
    else // line intersection
        return false;
};

const Color &TriangleMesh::intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene, float &t) const
{
    /* Tests intersection among all triangles in the mesh. Returns the closest intersection, if exists */

    float _t = -1;
    Color c;

    for (int i = 0; i < this->nTriangles; i++)
    {
        if ((this->triangles[i]).intersect(camOrigin, rayVec, _t))
        {
            if (_t < t)
            {
                t = _t;
                c = this->color;
            }
        }
    }
    if (_t != -1)
        return this->color;
    return scene.backgroundColor;
};