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
