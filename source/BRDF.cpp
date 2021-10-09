#include "BRDF.h"

Elite::RGBColor BRDF::Lambert(float diffuseReflectance, const Elite::RGBColor& diffuseColor)
{
    return diffuseColor * (diffuseReflectance / float(E_PI));
}

Elite::RGBColor BRDF::Phong(float specularReflectance, float phongExponent, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection, const Elite::FVector3& normal)
{
    Elite::FVector3 reflect{ lightDirection - 2 * (Elite::Dot(normal, lightDirection) * normal) };
    Elite::Normalize(reflect);
    float cosAlpha{ acos(cos(Elite::Dot(reflect, viewDirection))) };
    float specularReflection{ specularReflectance * pow(cosAlpha, phongExponent) };
    return Elite::RGBColor(specularReflection, specularReflection, specularReflection);
}

Elite::RGBColor BRDF::CookTorrence(const Elite::FVector3& light, const Elite::FVector3& view, const Elite::FVector3& normal, float roughnessSquared, const Elite::RGBColor& F0)
{
    const Elite::FVector3 lightAndView{ view + light };
    const Elite::FVector3 half{ lightAndView / Elite::Magnitude(lightAndView) };

    Elite::RGBColor numerator = Schlick(half, view, F0) * TrowbridgeReitzGGX(normal, half, roughnessSquared) * SchlickSmith(normal, view, light, roughnessSquared);
    float denom{ 4 * Elite::Dot(view, normal) * Elite::Dot(light, normal) };
    return numerator / denom;
}

float BRDF::TrowbridgeReitzGGX(const Elite::FVector3& normal, const Elite::FVector3& half, float roughnessSquared)
{
    float dotSquared{ static_cast<float>(pow(Elite::Dot(normal, half), 2)) };
    float denom{static_cast<float>(E_PI) * static_cast<float>(pow(dotSquared * (roughnessSquared - 1) + 1, 2))};
    return roughnessSquared / denom;
}

Elite::RGBColor BRDF::Schlick(const Elite::FVector3& half, const Elite::FVector3& view, const Elite::RGBColor& F0)
{
    float temp{ static_cast<float>(pow(1 - Elite::Dot(half, view), 5)) };
    Elite::RGBColor identity{ 1,1,1 };
    return F0 + (identity - F0) * temp;
}

float BRDF::SchlickSmith(const Elite::FVector3& normal, const Elite::FVector3& view, const Elite::FVector3& light, float roughnessSquared)
{
    float k{ static_cast<float>(pow(roughnessSquared + 1, 2)) / 8.f };
    return SchlickGGX(normal, view, k) * SchlickGGX(normal, light, k);
}

float BRDF::SchlickGGX(const Elite::FVector3& normal, const Elite::FVector3& view, float k)
{
    float dotProduct{ Elite::Dot(normal, view) };
    float denom{ dotProduct * (1 - k) + k };
    return dotProduct / denom;
}
