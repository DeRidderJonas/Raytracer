#pragma once
#include "Light.h"
class DirectionalLight final : public Light
{
public:
	DirectionalLight(float intensity, const Elite::FVector3& direction, const Elite::RGBColor& color);
	virtual ~DirectionalLight() = default;

	virtual Elite::FVector3 GetDirection(const Elite::FPoint3& posToShade) const override;
private:
	Elite::FVector3 m_Direction;
};

