#include "Ray.h"

Ray::Ray(const Elite::FPoint3& origin, const Elite::FVector3& direction)
    : m_Origin{origin}
    , m_Direction{direction}
{
}

bool Ray::isValidTValue(float t) const
{
    return t > tMin && t < tMax;
}

void Ray::SetMaxTValue(float value)
{
    tMax = value;
}
