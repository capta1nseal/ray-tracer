#ifndef _RAYTRACERPRIMITIVEOBJECT_
#define _RAYTRACERPRIMITIVEOBJECT_


#include "raymath/vec3.hpp"
#include "geometry/primitives/primitives.hpp"


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
