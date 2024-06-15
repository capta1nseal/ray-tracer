#ifndef _RAYTRACERPLANE_
#define _RAYTRACERPLANE_


#include "../raymath/raymath.hpp"


/*
Geometric parallelogram on a plane.
Most common use case expected to be rectangles
Implements boolean ray intersection check.
*/
struct Plane
{
    // Position of one rectangle corner from world origin. Acts as origin for edge1 and edge2.
    Vec3 corner;
    // Represents two parallel edges with origins of corner and corner + edge2.
    Vec3 edge1;
    // Represents two parallel edges with origins of corner and corner + edge1.
    Vec3 edge2;

    Plane(const Vec3& initCorner = Vec3(), const Vec3& initEdge1 = Vec3(), const Vec3& initEdge2 = Vec3());

    // return -1.0f if no intersection, otherwise distance to intersection.
    float intersectRay(const Ray& ray) const;
};


#endif
