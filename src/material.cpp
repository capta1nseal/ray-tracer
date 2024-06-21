#include "material.hpp"


Material::Material(
    Vec3<double> initColor, Vec3<double> initSpecularColor, Vec3<double> initEmissionColor,
        double initSpecularProbability, double initSmoothness, double initEmissionStrength
)
    : color(initColor), specularColor(initSpecularColor), emissionColor(initEmissionColor), specularProbability(initSpecularProbability), smoothness(initSmoothness), emissionStrength(initEmissionStrength)
{}
