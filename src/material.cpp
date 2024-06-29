#include "material.hpp"


#include <cmath>
#include <iostream>

#include "raymath/raymath.hpp"


Material::Material(
    Vec3<double> initColor, Vec3<double> initEmissionColor,
        double initIOR, double initRoughness, double initEmissionStrength
)
    : color(initColor), emissionColor(initEmissionColor), IOR(initIOR), roughness(initRoughness), emissionStrength(initEmissionStrength)
{}

double Material::fresnel(double outDotMicroNormal) const
{
    double normalReflectance = std::pow((IOR - 1.0) / (IOR + 1.0), 2.0);
    return normalReflectance + (1.0 - normalReflectance) * std::pow(1.0 - outDotMicroNormal, 5.0);
}

double Material::geometricAttenuation(const Vec3<double> incoming, const Vec3<double> outgoing, const Vec3<double> macroNormal, const Vec3<double> microNormal) const
{
    double twoMicroDotMacro = 2.0 * (microNormal * macroNormal);
    double outgoingDotMicro = outgoing * microNormal;

    if (outgoingDotMicro <= 0.0 or (incoming * macroNormal) <= 0.0) return 0.0;

    return std::clamp(
        std::min(
            (twoMicroDotMacro * (macroNormal * outgoing)) / outgoingDotMicro,
            (twoMicroDotMacro * (macroNormal * incoming)) / outgoingDotMicro
        ),
        0.0, 1.0
    );
}

double Material::sampleNormal(double pitchFactor) const
{
    return std::atan(roughness * roughness * std::sqrt(pitchFactor / (1.0 - pitchFactor)));
}

double Material::NDF(double normalPitch) const
{
    double a = roughness * roughness;
    double cosPitch = std::cos(normalPitch);
    double temp = ((a * a) - 1.0) * cosPitch * cosPitch + 1.0;
    return (a * a) / (pi * temp * temp);
}

double Material::PDF(double samplePitch, double outDotMicroNormal) const
{
    return PDFNormal(samplePitch) / (4.0 * outDotMicroNormal);
}

double Material::PDFNormal(double normalPitch) const
{
    return tau * NDF(normalPitch) * std::cos(normalPitch);
}
