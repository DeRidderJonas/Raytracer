#include "Plane.h"

Plane::Plane(const Elite::FPoint3& origin, Material* pMaterial, const Elite::FVector3& normal, Cullmode cullmode)
	: Object(origin, pMaterial, cullmode)
	, m_Normal{normal}
{
}

void Plane::Transform(const Elite::FMatrix4& transform)
{
}

bool Plane::Hit(const Ray& ray, HitRecord& hitRecord) const
{
	Elite::Vector<3, float> rayToPlane = (m_Origin - ray.m_Origin);
	float dotRayDirectionNormal{ Elite::Dot(ray.m_Direction, m_Normal) };

	if (m_Cullmode == Cullmode::FrontFaceCulling && dotRayDirectionNormal < 0) return false;
	if (m_Cullmode == Cullmode::BackFaceCulling && dotRayDirectionNormal > 0) return false;

	float t = Elite::Dot(rayToPlane, m_Normal)/dotRayDirectionNormal;
	
	if(!ray.isValidTValue(t)) return false;

	hitRecord.tValue = t;
	hitRecord.hitPoint = ray.m_Origin + t * ray.m_Direction;
	hitRecord.color = m_Material->getColor();
	if (dotRayDirectionNormal > 0) hitRecord.normal = -m_Normal;
	else hitRecord.normal = m_Normal;

	return true;
}
