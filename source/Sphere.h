#pragma once
#include "Object.h"

class Sphere final : public Object
{
public:
	Sphere(const Elite::FPoint3& origin, Material* pMaterial, float radius, Cullmode cullmode = Cullmode::NoCulling);

	bool Hit(const Ray& ray, HitRecord& hitrecord) const override;
private:
	float m_Radius;
};

