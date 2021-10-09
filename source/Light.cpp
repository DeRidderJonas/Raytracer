#include "Light.h"

Light::Light(float intensity, const Elite::RGBColor& color)
	: m_Intensity{intensity}
	, m_Color{color}
{
}

Elite::RGBColor Light::GetIrradiance(const Elite::FPoint3& posToShade)
{
	Elite::FVector3 direction{ GetDirection(posToShade) };
	float sqrDistance{ Elite::SqrMagnitude(direction) };
	return m_Color * (m_Intensity / sqrDistance);
}
