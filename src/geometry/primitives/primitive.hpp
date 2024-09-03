#ifndef _RAYTRACERPRIMITIVE_
#define _RAYTRACERPRIMITIVE_


#include <memory>

#include "../../raymath/raymath.hpp"


struct Primitive
{
    virtual ~Primitive() = default;

    virtual std::unique_ptr<Primitive> clone() const = 0;

    virtual HitInfo intersectRay(const Ray& ray) const = 0;
};


#endif
