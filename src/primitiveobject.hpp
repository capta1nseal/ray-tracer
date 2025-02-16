#ifndef _RAYTRACERPRIMITIVEOBJECT_
#define _RAYTRACERPRIMITIVEOBJECT_


#include <memory>

#include "geometry/primitives/primitives.hpp"


/*
Wrapper for a Primitive and material.
*/
struct PrimitiveObject
{
    std::unique_ptr<Primitive> primitive;
    std::shared_ptr<Material> material;

    template <typename T>
    PrimitiveObject(T initPrimitive, std::shared_ptr<Material> initMaterial)
        : primitive(std::make_unique<T>(std::move(initPrimitive))), material(initMaterial) {}
    
    PrimitiveObject(const PrimitiveObject& other)
        : primitive(other.primitive->clone()), material(other.material) {}

    PrimitiveObject(PrimitiveObject&& other) noexcept
        : primitive(std::move(other.primitive)), material(std::move(other.material)) {}
};


#endif
