#ifndef _RAYTRACERPRIMITIVEINTERSECTOR_
#define _RAYTRACERPRIMITIVEINTERSECTOR_


#include "../raymath/raymath.hpp"
#include "primitives/primitives.hpp"


/*
Visitor means to be used with std::visit, in order to calculate the ray intersection of a ray with a Primitive
*/
template<Vec3Basis T>
struct PrimitiveIntersector
{
    Ray<T>* ray;

    PrimitiveIntersector() : ray(nullptr) {}

    PrimitiveIntersector& with(Ray<T>* newRay)
    {
        ray = newRay;
        return *this;
    }

    template<isPrimitive U>
    auto operator()(const U& primitive)
    {
        return primitive.intersectRay(*ray);
    }
};


#endif
