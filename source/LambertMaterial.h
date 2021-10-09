#pragma once
#include "Material.h"
class LambertMaterial final : public Material
{
public:
	LambertMaterial(float reflectance, const Elite::RGBColor& color);
	virtual ~LambertMaterial() = default;

	virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& wIncoming, const Elite::FVector3& wOutgoing) const override;
private:
	float m_Reflectance;
};

