#pragma once
#include "Light.h"

class PointLight final : public Light
{
public:
	PointLight(float intensity, const Elite::FPoint3& position, const Elite::RGBColor& color);
	virtual ~PointLight() = default;

	virtual Elite::FVector3 GetDirection(const Elite::FPoint3& posToShade) const override;
private:
	Elite::FPoint3 m_Position;
};

