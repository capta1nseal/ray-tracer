#ifndef _RAYTRACERMATERIAL_
#define _RAYTRACERMATERIAL_


#include "raymath/vec3.hpp"
#include "raymath/direction.hpp"


/*
Wrapper for data used in the basic material model.
Has constant equidirectional emission.
Represents a microfacet shading model using the GGX NDF and sampling accordingly.
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

    // Sample a microfacet normal according to the GGX NDF.
    // Returns only the pitch relative to normal, yaw can be sampled uniformly.
    // Requires a uniform random value in [0,1]
    double sampleNormal(double pitchFactor) const;
    // Calculate the GGX normal distribution function.
    // Independent of yaw, since it is sampled uniformly.
    double NDF(double normalPitch) const;
    // Calculate the PDF of a sample generated.
    // Based upon the GGX normal distribution function.
    // Requires the pitch of the sample relative to macrosurface normal,
    // and the dot product between the outgoing direction and the microsurface normal.
    double PDF(double samplePitch, double outDotNormal) const;
};


#endif
