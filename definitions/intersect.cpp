#include "entities.h"

/*
    Intersections
*/

// all classes are currently defined in stubs (this will be solved when merging the implementation of the group)

const Color &Sphere::intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene) const
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

const Color &Plane::intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene) const
{
    float a = vec3::dot(rayVec, this->normal);
    if (a == 0)
        return scene.backgroundColor;
    else
        return this->color;

    // point of intersection:
    // float b = vec3::dot(camOrigin, this->normal) - vec3::dot(this->origin, this->normal);
    // float t = -b / a;
    // return camOrigin + rayVec * t;
};

const bool TriangleMesh::triangleIntersect(const vec3& rayVec, const Triangle& triangle) const {
    float a = vec3::dot(rayVec, triangle.normal);
    if (a == 0)
        return false;
    else
        return true;

    // point of intersection:
    // float b = vec3::dot(camOrigin, this->normal) - vec3::dot(this->origin, this->normal);
    // float t = -b / a;
    // float[3] intersectPoint = camOrigin + rayVec * t;
    
    // baricentric coordinates:
    // float[3] coordinates = findBaricentricCoordinates(intersectPoint, triangle);
    // if (isInsideTriangle(coordinates))
    //    return true;
    // return false;
};

const Color &TriangleMesh::intersect(const point3 &camOrigin, const vec3 &rayVec, const Scene &scene) const {
    bool intersected;
    // Triangle* closestTriangle;
    for (int i = 0; i < this->nTriangles; i ++) {
        if (this->triangleIntersect(rayVec, this->triangles[i]))
            return this->color;
            // intersected = true;
            // closestTriangle = this->triangles[i];
    }
    // if (intersected)
    //    return this->triangles[i]->color;
    return scene.backgroundColor;
};