#include "world.hpp"


#include <vector>

#include "raymath/raymath.hpp"
#include "geometry/geometry.hpp"


World::World()
{
    primitives.reserve(2);
    primitiveCount += 1;
    primitives.push_back(
        Plane(
            Vec3( 0.0f, 0.0f,-2.0f),
            Vec3( 0.0f,-2.0f, 2.0f),
            Vec3( 0.0f, 2.0f, 2.0f)
        )
    );
    primitiveCount += 1;
    primitives.push_back(
        Sphere(
            Vec3( 0.0f, 2.0f, 2.0f),
            1.0f
        )
    );
    primitives.resize(primitiveCount);
}

const std::vector<Primitive>& World::getPrimitives() const
{
    return primitives;
}
