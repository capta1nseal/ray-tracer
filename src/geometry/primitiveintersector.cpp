#include "primitiveintersector.hpp"


#include <type_traits>

#include "../raymath/ray.hpp"
#include "../raymath/hitinfo.hpp"
#include "primitives/primitives.hpp"


PrimitiveIntersector::PrimitiveIntersector() : ray(nullptr)
{
}

PrimitiveIntersector& PrimitiveIntersector::with(Ray* newRay)
{
    ray = newRay;
    return *this;
}
