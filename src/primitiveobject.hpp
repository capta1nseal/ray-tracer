#ifndef _RAYTRACERPRIMITIVEOBJECT_
#define _RAYTRACERPRIMITIVEOBJECT_


#include "raymath/raymath.hpp"
#include "geometry/primitives/primitives.hpp"


/*
Wrapper for a Primitive and material.
Simple to pack into an std::vector.
A visitor such as in geometry/primitiveintersector.hpp is required with std::visit to access Primitive methods.
*/
template<Vec3Basis T>
class PrimitiveObject
{
public:
    template<Vec3Basis U>
    PrimitiveObject(Primitive<U> initPrimitive, Material initMaterial)
        : primitive(initPrimitive), material(initMaterial) {}
    template<isPrimitive U>
    PrimitiveObject(U initPrimitive, Material initMaterial)
        : primitive(initPrimitive), material(initMaterial) {}
    // Cast from different precision of primitiveObject.
    template<Vec3Basis U>
    PrimitiveObject(const PrimitiveObject<U>& other)
        : primitive(other.primitive), material(other.material) {}

    const auto& getPrimitive() const
    {
        return primitive;
    }
    const auto& getMaterial() const
    {
        return material;
    }

private:
    Primitive<T> primitive;
    Material material;
};


#endif
