#ifndef _RAYTRACERENVIRONMENT_
#define _RAYTRACERENVIRONMENT_


#include "raymath/raymath.hpp"


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

    // Get a random direction pointing towards a point on the sun.
    // Requires a uniform random angle in [-pi,pi], and a uniform random value in [0,1]
    Vec3<double> sampleSun(double yaw, double pitchValue) const;

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
