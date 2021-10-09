#pragma once
#include "ERGBColor.h"
#include "EMath.h"
#include "Ray.h"
class Material
{
public:
	enum class BaseMaterial
	{
		Titanium,
		Chromium,
		Iron,
		Nickel,
		Platinum,
		Copper,
		Palladium,
		Mercury,
		Brass,
		Zinc,
		Gold,
		Aluminum,
		Silver,
		Dielectric
	};
	Material(const Elite::RGBColor& color);
	virtual ~Material() = default;

	virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& wIncoming, const Elite::FVector3& wOutgoing) const = 0;

	const Elite::RGBColor& getColor() const;

	static Elite::RGBColor GetColorForMetal(const BaseMaterial& metal = BaseMaterial::Dielectric);
protected:
	Elite::RGBColor m_Color;
};

