#ifndef _RAYTRACERPRIMITIVES_
#define _RAYTRACERPRIMITIVES_


/*
Wrapper header for primitive geometric shapes, and useful definitions for working with their types.
*/


#include <variant>

#include "plane.hpp"
#include "sphere.hpp"


// A variant type wrapping all primitives
using Primitive = std::variant<Plane, Sphere>;

// All primitives implement HitInfo intersectRay(const Ray& ray)
template<typename T>
concept isPrimitive = std::is_same<T, Plane>::value || std::is_same<T, Sphere>::value;


#endif

