#ifndef _RAYTRACERPRIMITIVEINTERSECTOR_
#define _RAYTRACERPRIMITIVEINTERSECTOR_


#include <type_traits>

#include "../raymath/ray.hpp"
#include "../raymath/hitinfo.hpp"
#include "primitives/primitives.hpp"


/*
Visitor means to be used with std::visit, in order to calculate the ray intersection of a ray with a Primitive
*/
struct PrimitiveIntersector
{
    Ray* ray;

    PrimitiveIntersector();

    PrimitiveIntersector& with(Ray* newRay);

    template<isPrimitive T>
    HitInfo operator()(const T& primitive)
    {
        return primitive.intersectRay(*ray);
    }
};


#endif
