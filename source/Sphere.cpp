#include "Sphere.h"

Sphere::Sphere(const Elite::FPoint3& origin, Material* pMaterial, float radius, Cullmode cullmode)
	: Object(origin, pMaterial, cullmode)
	, m_Radius{radius}
{
}

bool Sphere::Hit(const Ray& ray, HitRecord& hitrecord) const
{
	Elite::Vector<3, float> rayToOrigin{ ray.m_Origin - m_OriginWorld };
	float a{ Elite::Dot(ray.m_Direction, ray.m_Direction) };
	float b{ 2 * Elite::Dot(ray.m_Direction, rayToOrigin) };
	float c{ Elite::Dot(rayToOrigin, rayToOrigin) - Elite::Square(m_Radius) };
	float discriminant{ Elite::Square(b) - 4 * a * c };
	bool flipNormal{ false };

	if (discriminant < 0)
	{
		return false;
	}
	
	float t{};

	if (discriminant < 0.0001f)
	{
		t = -b / (2 * a);
		if (!ray.isValidTValue(t)) return false;
	}

	if (discriminant > 0.0001f)
	{
		float discriminantSqrt{ sqrt(discriminant) };
		float t1{ (-b - discriminantSqrt) / (2 * a) };
		float t2{ (-b + discriminantSqrt) / (2 * a) };

		if (ray.isValidTValue(t1)) t = t1;
		else if (ray.isValidTValue(t2))
		{
			t = t2;
			flipNormal = true;
		}
	}

	if (ray.isValidTValue(t))
	{
		hitrecord.tValue = t;
		hitrecord.hitPoint = ray.m_Origin + t * ray.m_Direction;
		hitrecord.color = m_Material->getColor();
		hitrecord.normal = (hitrecord.hitPoint - m_Origin) / m_Radius;
		if (flipNormal) hitrecord.normal *= -1;

		if (m_Cullmode == Cullmode::NoCulling) return true;
		float cullResult{ Elite::Dot(ray.m_Direction, hitrecord.normal) };
		if (m_Cullmode == Cullmode::FrontFaceCulling) return cullResult > 0;
		if (m_Cullmode == Cullmode::BackFaceCulling) return cullResult < 0;
	}

	return false;
}
