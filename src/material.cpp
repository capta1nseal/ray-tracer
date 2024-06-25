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

Direction<double> Material::sampleNormal(double yaw, double pitchFactor) const
{
    return {
        yaw,
        std::atan(smoothness * std::sqrt(pitchFactor / (1.0 - pitchFactor)))
    };
}

double Material::NDF(double pitch) const
{
    double cosPitch = std::cos(pitch);
    double temp = (smoothness * smoothness - 1) * cosPitch * cosPitch + 1;
    return (smoothness * smoothness * cosPitch * std::sin(pitch)) / (pi * temp * temp);
}
