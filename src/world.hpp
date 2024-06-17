#ifndef _RAYTRACERWORLD_
#define _RAYTRACERWORLD_


#include <vector>

#include "raymath/raymath.hpp"
#include "geometry/geometry.hpp"


/*
Wrapper for all scene geometry and materials.
*/
class World
{
public:
    World();

    const std::vector<Primitive>& getPrimitives() const;

private:
    unsigned int primitiveCount;
    std::vector<Primitive> primitives;
};


#endif
