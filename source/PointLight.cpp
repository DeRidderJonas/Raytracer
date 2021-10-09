#include "PointLight.h"

PointLight::PointLight(float intensity, const Elite::FPoint3& position, const Elite::RGBColor& color)
	: Light(intensity, color)
	, m_Position{position}
{
}

Elite::FVector3 PointLight::GetDirection(const Elite::FPoint3& posToShade) const
{
	return m_Position - posToShade;
}
