#ifndef _RAYTRACERPRIMITIVES_
#define _RAYTRACERPRIMITIVES_


/*
Wrapper header for primitive geometric shapes, and useful definitions for working with them.
*/


#include <variant>
#include <concepts>
#include <type_traits>

#include "primitive.hpp"
#include "plane.hpp"
#include "sphere.hpp"


// A way to create a type constraint for a specialization of a template.
template<template<typename> class Template, typename T>
struct is_specialization_of : std::false_type { };

template<template<typename> class Template, typename T>
struct is_specialization_of<Template, Template<T>> : std::true_type { };

// All primitives implement HitInfo intersectRay(const Ray& ray).
template<typename T>
concept isPrimitive = std::derived_from<Primitive, T>;


#endif
