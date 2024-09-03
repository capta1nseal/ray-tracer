#ifndef _RAYTRACERWORLD_
#define _RAYTRACERWORLD_


#include <vector>

#include "primitiveobject.hpp"
#include "environment.hpp"


/*
Wrapper for all scene geometry and materials.
Currently only holds primitive objects' geometry, since there are no normal models (yet).
*/
class Scene
{
public:
    Scene();

    // Add a primitive object to the scene.
    // Memory is managed dynamically, reserving space manually is not necessary.
    void addPrimitiveObject(const PrimitiveObject& primitiveObject);

    // Attempt to reserve space for n primitive objects more than currently stored.
    // Can be useful if a very large number of objects will be added and the number is known beforehand.
    // Excess space that was not then used can be trimmed with shrinkToFit.
    void reservePrimitiveObjects(std::size_t n);

    // Attempt to shrink all dynamically allocated lists containing data to their precise size, trimming off all excess capacity.
    // Useful if a bunch of space has been reserved through reservePrimitiveObjects but then never used.
    void shrinkToFit();

    const std::vector<PrimitiveObject>& getPrimitiveObjects() const;

    // Get the incoming light from the environment from specified direction.
    Vec3<double> getEnvironmentEmission(const Vec3<double>& direction) const;

private:
    std::vector<PrimitiveObject> primitiveObjects;

    Environment environment;
};


#endif
