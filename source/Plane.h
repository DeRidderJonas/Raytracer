#pragma once
#include "Object.h"
class Plane final : public Object
{
public:
	Plane(const Elite::FPoint3& origin, Material* pMaterial, const Elite::FVector3& normal, Cullmode cullmode = Cullmode::NoCulling);

	virtual void Transform(const Elite::FMatrix4& transform) override;
	bool Hit(const Ray& ray, HitRecord& hitRecord) const override;
private:
	Elite::FVector3 m_Normal;
};

