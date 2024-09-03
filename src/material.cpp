#include "material.hpp"


#include <cmath>

#include "raymath/vec3.hpp"
#include "raymath/direction.hpp"
#include "raymath/usefulfunctions.hpp"
#include "raymath/constants.hpp"


Material::Material(
    Vec3<double> initColor, Vec3<double> initSpecularColor, Vec3<double> initEmissionColor,
        double initSpecularProbability, double initSmoothness, double initEmissionStrength
)
    : color(initColor), specularColor(initSpecularColor), emissionColor(initEmissionColor), specularProbability(initSpecularProbability), smoothness(initSmoothness), emissionStrength(initEmissionStrength)
{}

double Material::sampleNormal(double pitchFactor) const
{
    return std::atan(smoothness * std::sqrt(pitchFactor / (1.0 - pitchFactor)));
}

double Material::NDF(double normalPitch) const
{
    double cosPitch = std::cos(normalPitch);
    double temp = (smoothness * smoothness - 1) * cosPitch * cosPitch + 1;
    return (smoothness * smoothness * cosPitch * std::sin(normalPitch)) / (pi * temp * temp);
}

double Material::PDF(double samplePitch, double outDotNormal) const
{
    return NDF(samplePitch) / (4.0 * outDotNormal);
}
