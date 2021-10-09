#include "LambertMaterial.h"
#include "BRDF.h"
LambertMaterial::LambertMaterial(float reflectance, const Elite::RGBColor& color)
	: Material(color)
	, m_Reflectance{reflectance}
{
}

Elite::RGBColor LambertMaterial::Shade(const HitRecord& hitRecord, const Elite::FVector3& wIncoming, const Elite::FVector3& wOutgoing) const
{
	return BRDF::Lambert(m_Reflectance, m_Color);
}
