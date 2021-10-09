#pragma once
#include "Material.h"

class LambertPhongMaterial final : public Material
{
	public:
		LambertPhongMaterial(float diffuseReflectance, const Elite::RGBColor& color, float specularReflectance, float phongExponent);
		virtual ~LambertPhongMaterial() = default;

		virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& wIncoming, const Elite::FVector3& wOutgoing) const override;
	private:
		float m_DiffuseReflectance;
		float m_SpecularReflectance;
		float m_PhongExponent;
};

