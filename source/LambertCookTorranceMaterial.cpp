#include "LambertCookTorranceMaterial.h"
#include "BRDF.h"

LambertCookTorranceMaterial::LambertCookTorranceMaterial(bool isMetal, float roughness, const Elite::RGBColor& color)
	: Material(color)
	, m_IsMetal{isMetal}
	, m_RoughnessSquared{static_cast<float>(pow(roughness, 2))}
{
}

Elite::RGBColor LambertCookTorranceMaterial::Shade(const HitRecord& hitRecord, const Elite::FVector3& wIncoming, const Elite::FVector3& wOutgoing) const
{
	Elite::RGBColor specular{ BRDF::CookTorrence(wIncoming, wOutgoing, hitRecord.normal, m_RoughnessSquared, m_Color) };
	float fresnel{ Elite::Dot(-wOutgoing, hitRecord.normal) };
	Elite::RGBColor diffuse{ m_IsMetal ? Elite::RGBColor(0,0,0) : BRDF::Lambert(1 - fresnel, m_Color) };
	
	return diffuse + specular;
}
