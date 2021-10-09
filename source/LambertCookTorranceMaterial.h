#pragma once
#include "Material.h"

class LambertCookTorranceMaterial final : public Material
{
public:
	LambertCookTorranceMaterial(bool isMetal, float roughness, const Elite::RGBColor& color);
	virtual ~LambertCookTorranceMaterial() = default;

	virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& wIncoming, const Elite::FVector3& wOutgoing) const override;
private:
	bool m_IsMetal;
	float m_RoughnessSquared;
};

