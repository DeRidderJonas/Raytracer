#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(float intensity, const Elite::FVector3& direction, const Elite::RGBColor& color)
	: Light(intensity, color)
	, m_Direction{direction}
{
	Elite::Normalize(m_Direction);
}

Elite::FVector3 DirectionalLight::GetDirection(const Elite::FPoint3& posToShade) const
{
	return m_Direction;
}
