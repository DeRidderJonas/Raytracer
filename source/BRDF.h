#pragma once
#include "ERGBColor.h"
#include "EMath.h"
class BRDF final
{
public:
	static Elite::RGBColor Lambert(float diffuseReflectance, const Elite::RGBColor& diffuseColor);
	static Elite::RGBColor Phong(float specularReflectance, float phongExponent, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection, const Elite::FVector3& normal);
	static Elite::RGBColor CookTorrence(const Elite::FVector3& light, const Elite::FVector3& view, const Elite::FVector3& normal, float roughnessSquared, const Elite::RGBColor& F0);
private:
	static float TrowbridgeReitzGGX(const Elite::FVector3& normal, const Elite::FVector3& half, float roughnessSquared);
	static Elite::RGBColor Schlick(const Elite::FVector3& half, const Elite::FVector3& view, const Elite::RGBColor& F0);
	static float SchlickSmith(const Elite::FVector3& normal, const Elite::FVector3& view, const Elite::FVector3& light, float roughnessSquared);
	static float SchlickGGX(const Elite::FVector3& normal, const Elite::FVector3& view, float k);
};

