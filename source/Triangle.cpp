#include "Triangle.h"

Triangle::Triangle(const Elite::FPoint3& v0, const Elite::FPoint3& v1, const Elite::FPoint3& v2, Material* pMaterial, Cullmode cullmode)
	: Object({}, pMaterial, cullmode)
	, m_V0{v0}
	, m_V1{v1}
	, m_V2{v2}
	, m_V0World{v0}
	, m_V1World{v1}
	, m_V2World{v2}
	, m_Normal{Elite::Cross(v1 - v0, v2 - v0)}
	, m_Center{(v0 + v1 + v2) / 3.f}
	, m_EdgeA{v1 - v0}
	, m_EdgeB{v2 - v1}
	, m_EdgeC{v0 - v2}
{
}

void Triangle::Transform(const Elite::FMatrix4& transform)
{
	m_V0World = Elite::FPoint3{ transform * Elite::FPoint4{ m_V0 } };
	m_V1World = Elite::FPoint3{ transform * Elite::FPoint4{ m_V1 } };
	m_V2World = Elite::FPoint3{ transform * Elite::FPoint4{ m_V2 } };

	m_Normal = Elite::Cross(m_V1World - m_V0World, m_V2World - m_V0World);
	m_Center = (m_V0World + m_V1World + m_V2World) / 3.f;
	m_EdgeA = m_V1World - m_V0World;
	m_EdgeB = m_V2World - m_V1World;
	m_EdgeC = m_V0World - m_V2World;
}

bool Triangle::Hit(const Ray& ray, HitRecord& hitRecord) const
{
	float dotRayNormal{ Elite::Dot(m_Normal, ray.m_Direction) };
	if(Elite::AreEqual(dotRayNormal, 0.f)) return false;
	if (m_Cullmode == Cullmode::FrontFaceCulling && dotRayNormal < 0) return false;
	if (m_Cullmode == Cullmode::BackFaceCulling && dotRayNormal > 0) return false;


	Elite::FVector3 L{ m_Center - ray.m_Origin };
	float t = Elite::Dot(L, m_Normal) / Elite::Dot(ray.m_Direction, m_Normal);
	if (!ray.isValidTValue(t)) return false;

	Elite::FPoint3 hitPoint{ ray.m_Origin + t * ray.m_Direction };

	Elite::FVector3 pointToSideA{ hitPoint - m_V0World };
	if (Elite::Dot(m_Normal, Elite::Cross(m_EdgeA, pointToSideA)) < 0) return false;

	Elite::FVector3 pointToSideB{ hitPoint - m_V1World };
	if (Elite::Dot(m_Normal, Elite::Cross(m_EdgeB, pointToSideB)) < 0) return false;

	Elite::FVector3 pointToSideC{ hitPoint - m_V2World };
	if (Elite::Dot(m_Normal, Elite::Cross(m_EdgeC, pointToSideC)) < 0) return false;

	hitRecord.color = m_Material->getColor();
	hitRecord.hitPoint = hitPoint;
	hitRecord.normal = m_Normal;
	hitRecord.tValue = t;

	return true;
}
