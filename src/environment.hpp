#ifndef _RAYTRACERENVIRONMENT_
#define _RAYTRACERENVIRONMENT_


#include "raymath/vec3.hpp"


/*
Wrapper for parameters of the environment texture,
and a method to get the incoming light from a given direction.
*/
class Environment
{
public:
    Environment();

    // Get the incoming light from the environment from specified direction.
    Vec3<double> getEmission(const Vec3<double>& direction) const;

private:
    Vec3<double> skyEmissionColor;
    double skyEmissionStrength;

    double sunRadiusScale;
    Vec3<double> sunEmissionColor;
    double sunEmissionStrength;
    // Normalized direction vector pointing towards sun.
    Vec3<double> sunDirection;
    // Sun radius is its angular radius in rad.
    double sunRadius;
    double cosSunRadius;
};


#endif
