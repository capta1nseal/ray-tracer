#ifndef _RAYTRACERMATERIAL_
#define _RAYTRACERMATERIAL_


#include "raymath/vec3.hpp"


/*
Wrapper for data used in the basic material model.
Has constant equidirectional emission.
Represents a microfacet shading model using the GGX NDF and sampling accordingly.
*/
struct Material
{
    Vec3<double> color;
    Vec3<double> emissionColor;
    double IOR;
    double roughness;
    double emissionStrength;

    Material(
        Vec3<double> initColor = {0.8, 0.8, 0.8}, Vec3<double> initEmissionColor = {0.8, 0.8, 0.8},
        double initIOR = {1.5}, double initRoughness = {0.5}, double initEmissionStrength = {0.0}
    );

    // Returns fresnel reflectance of reflection between outgoing ray and normal.
    // Requires dot product between outgoing direction and the microfacet normal.
    double fresnel(double outDotNormal) const;
    // Returns geometric attenuation term of reflection between incoming and outgoing
    // on surface with macrosurface normal and microfacet normal.
    double geometricAttenuation(const Vec3<double> incoming, const Vec3<double> outgoing, const Vec3<double> macroNormal, const Vec3<double> microNormal) const;

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
    // and the dot product between the outgoing direction and the microfacet normal.
    double PDF(double samplePitch, double outDotMicroNormal) const;
    // Calculate the PDF using the microsurface normal's pitch, instead of the generated sample.
    double PDFNormal(double normalPitch) const;
};


#endif
