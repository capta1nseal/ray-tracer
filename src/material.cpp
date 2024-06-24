#include "material.hpp"


#include "raymath/vec3.hpp"
#include "raymath/usefulfunctions.hpp"


const double pi = M_PI;
const double tau = 2.0 * pi;
const double oneOverPi = 1.0 / pi;
const double oneOverTau = 1.0 / tau;

Material::Material(
    Vec3<double> initColor, Vec3<double> initSpecularColor, Vec3<double> initEmissionColor,
        double initSpecularProbability, double initSmoothness, double initEmissionStrength
)
    : color(initColor), specularColor(initSpecularColor), emissionColor(initEmissionColor), specularProbability(initSpecularProbability), smoothness(initSmoothness), emissionStrength(initEmissionStrength)
{}
