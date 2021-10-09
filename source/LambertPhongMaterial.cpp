#include "LambertPhongMaterial.h"
#include "BRDF.h"

LambertPhongMaterial::LambertPhongMaterial(float diffuseReflectance, const Elite::RGBColor& color, float specularReflectance, float phongExponent)
	: Material(color)
	, m_DiffuseReflectance{diffuseReflectance}
	, m_SpecularReflectance{specularReflectance}
	, m_PhongExponent{phongExponent}
{
	float sum = diffuseReflectance + specularReflectance;
	if (sum > 1.f)
	{
		m_DiffuseReflectance = diffuseReflectance / sum;
		m_SpecularReflectance = specularReflectance / sum;
	}
}

Elite::RGBColor LambertPhongMaterial::Shade(const HitRecord& hitRecord, const Elite::FVector3& wIncoming, const Elite::FVector3& wOutgoing) const
{
	return BRDF::Lambert(m_DiffuseReflectance, m_Color) + BRDF::Phong(m_SpecularReflectance, m_PhongExponent, wIncoming, wOutgoing, hitRecord.normal);
}
