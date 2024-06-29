#include "scene.hpp"


#include <vector>

#include "primitiveobject.hpp"
#include "environment.hpp"
#include "raymath/raymath.hpp"
#include "geometry/geometry.hpp"


Scene::Scene()
    : environment() {}

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

Vec3<double> Scene::getEnvironmentEmission(const Vec3<double>& direction) const
{
    return environment.getEmission(direction);
}

Vec3<double> Scene::sampleSun(double yaw, double pitchValue) const
{
    return environment.sampleSun(yaw, pitchValue);
}
