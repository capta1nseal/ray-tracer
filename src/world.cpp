#include "world.hpp"


#include <vector>

#include "raymath/raymath.hpp"
#include "geometry/geometry.hpp"


World::World()
{
    primitives.reserve(6);
    primitiveCount += 1;
    primitives.push_back(
        Plane(
            Vec3(-15.0, 0.0, 0.0),
            Vec3(15.0,-15.0, 0.0),
            Vec3(15.0, 15.0, 0.0)
        )
    );
    primitiveCount += 1;
    primitives.push_back(
        Plane(
            Vec3(-2.0, 0.0, 0.0),
            Vec3( 2.0, 0.0, 4.0),
            Vec3( 2.0, 0.0, 1.0)
        )
    );
    primitiveCount += 1;
    primitives.push_back(
        Plane(
            Vec3( 2.0, 0.0, 0.0),
            Vec3(-2.0, 0.0, 4.0),
            Vec3(-2.0, 0.0, 1.0)
        )
    );
    primitiveCount += 1;
    primitives.push_back(
        Plane(
            Vec3( 0.0,-2.0, 0.0),
            Vec3( 0.0, 2.0, 4.0),
            Vec3( 0.0, 2.0, 1.0)
        )
    );
    primitiveCount += 1;
    primitives.push_back(
        Plane(
            Vec3( 0.0, 2.0, 0.0),
            Vec3( 0.0,-2.0, 4.0),
            Vec3( 0.0,-2.0, 1.0)
        )
    );
    primitiveCount += 1;
    primitives.push_back(
        Sphere(
            Vec3( 0.0, 0.0, 5.5),
            1.5
        )
    );
    primitives.resize(primitiveCount);
}

const std::vector<Primitive<double>>& World::getPrimitives() const
{
    return primitives;
}
