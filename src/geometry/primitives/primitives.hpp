#ifndef _RAYTRACERPRIMITIVES_
#define _RAYTRACERPRIMITIVES_


/*
Wrapper header for primitive geometric shapes, and useful definitions for working with their types.
*/


#include <variant>
#include <concepts>
#include <type_traits>

#include "plane.hpp"
#include "sphere.hpp"


// A variant type wrapping all primitives.
template<Vec3Basis T>
using Primitive = std::variant<Plane<T>, Sphere<T>>;

// A way to create a type constraint for a specialization of a template.
template<template<typename> class Template, typename T>
struct is_specialization_of : std::false_type { };

template<template<typename> class Template, typename T>
struct is_specialization_of<Template, Template<T>> : std::true_type { };

// All primitives implement HitInfo intersectRay(const Ray& ray).
template<typename T>
concept isPrimitive = is_specialization_of<Plane, T>::value || is_specialization_of<Sphere, T>::value;


#endif
