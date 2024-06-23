#include "scene.hpp"


#include <vector>

#include "primitiveobject.hpp"
#include "raymath/raymath.hpp"
#include "geometry/geometry.hpp"


Scene::Scene()
{
    // TODO remove all this code that just instantiates the demo scene.
    // Implement within application somehow, potentially in an encapsulated scene loading component.
    // That might also be a good time to start saving/loading scene data in/from files.
    Material groundMaterial = {
        {0.3, 0.3, 0.3},
        {0.9, 0.9, 0.9},
        {1.0, 1.0, 1.0},
        0.15,
        0.5,
        0.0
    };

    Material frameMaterial = {
        {0.5, 0.6, 0.3},
        {0.85, 0.85, 0.85},
        {1.0, 1.0, 1.0},
        0.3,
        0.67,
        0.0
    };

    Material ballMaterial = {
        {0.6, 0.3, 0.7},
        {0.7, 0.4, 0.8},
        {1.0, 1.0, 1.0},
        0.95,
        0.9,
        0.0
    };

    addPrimitiveObject(PrimitiveObject<double>(
        Plane(
            Vec3(-100.0, 0.0, 0.0),
            Vec3(100.0,-100.0, 0.0),
            Vec3(100.0, 100.0, 0.0)
        ),
        groundMaterial
    ));
    addPrimitiveObject(PrimitiveObject<double>(
        Plane(
            Vec3(-2.0, 0.0, 0.0),
            Vec3( 2.0, 0.0, 4.0),
            Vec3( 2.0, 0.0, 1.0)
        ),
        frameMaterial
    ));
    addPrimitiveObject(PrimitiveObject<double>(
        Plane(
            Vec3( 2.0, 0.0, 0.0),
            Vec3(-2.0, 0.0, 4.0),
            Vec3(-2.0, 0.0, 1.0)
        ),
        frameMaterial
    ));
    addPrimitiveObject(PrimitiveObject<double>(
        Plane(
            Vec3( 0.0,-2.0, 0.0),
            Vec3( 0.0, 2.0, 4.0),
            Vec3( 0.0, 2.0, 1.0)
        ),
        frameMaterial
    ));
    addPrimitiveObject(PrimitiveObject<double>(
        Plane(
            Vec3( 0.0, 2.0, 0.0),
            Vec3( 0.0,-2.0, 4.0),
            Vec3( 0.0,-2.0, 1.0)
        ),
        frameMaterial
    ));
    addPrimitiveObject(PrimitiveObject<double>(
        Sphere(
            Vec3(0.0, 0.0, 5.0),
            2.0
        ),
        ballMaterial
    ));
}

void Scene::addPrimitiveObject(const PrimitiveObject<double>& primitiveObject)
{
    primitiveObjects.push_back(primitiveObject);
}

void Scene::reservePrimitiveObjects(std::size_t n)
{
    primitiveObjects.reserve(primitiveObjects.size() + n);
}

void Scene::shrinkToFit()
{
    primitiveObjects.shrink_to_fit();
}

const std::vector<PrimitiveObject<double>>& Scene::getPrimitiveObjects() const
{
    return primitiveObjects;
}
