#include "entities.h"

/*
    Intersections
*/

// all classes are currently defined in stubs (this will be solved when merging the implementation of the group)

const Color &Sphere::intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene, point3 &outIntersectionPoint) const
{
    float a = vec3::dot(rayVec, rayVec);
    float b = 2.0f * (vec3::dot(camOrigin, rayVec) + vec3::dot(rayVec, this->center));
    float c = vec3::dot(camOrigin, camOrigin) + 2.0f * vec3::dot(camOrigin, this->center) + vec3::dot(this->center, this->center) - this->radius;
    float delta = b * b - 4.0f * a * c;

    if (delta >= 0.0f)
        return this->color;
    else
        return scene.backgroundColor;

    // point of intersection:
    // if (delta < 0)
    // {
    //     return NULL;
    // }
    // float t0 = -b - sqrt(delta) / 2a;
    // float t1 = -b + sqrt(delta) / 2a;
    // float t = (t0 < t1)? t0 : t1;
    // return camOrigin + rayVec * t;
};

const Color &Plane::intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene, point3 &outIntersectionPoint) const
{
    const float EPSILON = 0.0000001;

    // check if ray is parallel

    float a = vec3::dot(rayVec, this->normal);
    if (a > -EPSILON && a < EPSILON)
        return scene.backgroundColor; // ray is parallel

    // calculate intersection point

    float t = vec3::dot((this->origin - camOrigin), normal) / a;
    if (t > EPSILON) // intersect
    {
        outIntersectionPoint = camOrigin + t * rayVec;
        return this->color;
    }
    return scene.backgroundColor; // not intersect
};

const bool TriangleMesh::triangleIntersect(const point3 &rayOrigin, const vec3 &rayVec, const Triangle &t, point3 &outIntersectionPoint)
{
    /* Uses Moller-Trumbore intersection algorithm to chek intersection of a ray with triangles */

    const float EPSILON = 0.0000001;

    // triangle edge vectors

    vec3 edge1 = t[1] - t[0];
    vec3 edge2 = t[2] - t[0];
    vec3 h = vec3::cross(rayVec, edge2);

    // check if ray is parallel

    float a = vec3::dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return false; // ray is parallel

    // find beta coordinate

    float f = 1.0 / a;
    vec3 s = rayOrigin - t[0];
    float beta = f * vec3::dot(s, h);
    if (beta < 0.0 || beta > 1.0)
        return false; // outside triangle

    // find gamma coordinate

    vec3 q = vec3::cross(s, edge1);
    float gamma = f * vec3::dot(rayVec, q);
    if (gamma < 0.0 || beta + gamma > 1.0)
        return false; // outside triangle

    // find the intersection point

    float t = f * vec3::dot(edge2, q);
    if (t > EPSILON) // point intersection
    {
        outIntersectionPoint = rayOrigin + rayVec * t;
        return true;
    }
    else // line intersection
        return false;
};

const Color &TriangleMesh::intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene, point3 &outIntersectionPoint) const
{
    /* Tests intersection among all triangles in the mesh; only considers the closest one */

    point3 intersectionPoint;
    // Triangle* closestTriangle = nullptr;
    for (int i = 0; i < this->nTriangles; i++)
    {
        if (this->triangleIntersect(camOrigin, rayVec, this->triangles[i], intersectionPoint))
        {
            return this->color;
            // if (distance(this.triangles[i]) < distance(closestTriangle))
            // {
            //    closestTriangle = this->triangles[i];
            //    outIntersectionPoint = intersectionPoint;
            // }
        }
    }
    // if (closestTriangle != nullptr)
    //    return this->triangles[i]->color;
    return scene.backgroundColor;
};