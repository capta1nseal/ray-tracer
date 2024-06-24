#ifndef _RAYTRACERMATERIAL_
#define _RAYTRACERMATERIAL_


#include "raymath/vec3.hpp"


/*
Wrapper for data used in the basic material model.
*/
struct Material
{
    Vec3<double> color;
    Vec3<double> specularColor;
    Vec3<double> emissionColor;
    double specularProbability;
    double smoothness;
    double emissionStrength;

    Material(
        Vec3<double> initColor = {0.8, 0.8, 0.8}, Vec3<double> initSpecularColor = {0.8, 0.8, 0.8}, Vec3<double> initEmissionColor = {0.8, 0.8, 0.8},
        double initSpecularProbability = {0.5}, double initSmoothness = {0.5}, double initEmissionStrength = {0.0}
    );
};


#endif
