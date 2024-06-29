#include "environment.hpp"


#include <cmath>

#include "raymath/raymath.hpp"


Environment::Environment()
{
    skyEmissionColor = {0.5, 0.5, 1.0};
    skyEmissionStrength = 1.0;

    sunRadiusScale = 10.0;
    sunEmissionColor = {0.9922, 0.9843, 0.8275};
    sunEmissionStrength = 2.0e4 / (sunRadiusScale * sunRadiusScale);
    sunDirection = Vec3(-12.5, 35.0, 20.0).normalized();
    sunRadius = (0.5 * M_PI / 180.0) * sunRadiusScale;
    cosSunRadius = std::cos(sunRadius);
}

Vec3<double> Environment::getEmission(const Vec3<double>& direction) const
{
    double skyRayElevation = (direction.z + 1.0) / 2.0;
    // Crude estimation of incoming light from blue sky.
    Vec3<double> emittedLight =
        skyEmissionColor * skyEmissionStrength *
        std::max(skyRayElevation * skyRayElevation, 0.0);

    // If ray points towards sun, add sun's emission to incoming light.
    return (direction * sunDirection > cosSunRadius) ? emittedLight + sunEmissionColor * sunEmissionStrength : emittedLight;
}

Vec3<double> Environment::sampleSun(double yaw, double pitchValue) const
{
    return rotateAroundSelfUnit(sunDirection, yaw, pitchValue * sunRadius);
}
