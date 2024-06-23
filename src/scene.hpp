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

    void addPrimitiveObject(const PrimitiveObject<double>& primitiveObject);

    // Attempt to reserve space for n primitive objects than currently stored.
    void reservePrimitiveObjects(std::size_t n);

    // Attempt to shrink all dynamically allocated lists containing data to their precise size, trimming off all excess capacity.
    // Useful if a bunch of space has been reserved through reservation methods but then never used.
    void shrinkToFit();

    const std::vector<PrimitiveObject<double>>& getPrimitiveObjects() const;

    Vec3<double> getEnvironmentEmission(const Vec3<double>& direction) const;

private:
    std::vector<PrimitiveObject<double>> primitiveObjects;

    Environment environment;
};


#endif
