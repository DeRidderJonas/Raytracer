#pragma once
#include "ERGBColor.h"
#include "EMath.h"

class Light
{
public:
	Light(float intensity, const Elite::RGBColor& color);
	virtual ~Light() = default;

	virtual Elite::RGBColor GetIrradiance(const Elite::FPoint3& posToShade);

	//Light vector NOT normalized
	virtual Elite::FVector3 GetDirection(const Elite::FPoint3& posToShade) const = 0;
private:
	float m_Intensity;
	Elite::RGBColor m_Color;
};

