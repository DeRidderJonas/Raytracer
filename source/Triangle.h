#pragma once
#include "Object.h"
#include "EMath.h"

class Triangle final : public Object
{
public:
	Triangle(const Elite::FPoint3& v0, const Elite::FPoint3& v1, const Elite::FPoint3& v2, Material* pMaterial, Cullmode cullmode = Cullmode::NoCulling);
	~Triangle() = default;

	virtual void Transform(const Elite::FMatrix4& transform) override;
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord) const;
private:
	Elite::FPoint3 m_V0;
	Elite::FPoint3 m_V1;
	Elite::FPoint3 m_V2;

	Elite::FPoint3 m_V0World;
	Elite::FPoint3 m_V1World;
	Elite::FPoint3 m_V2World;

	Elite::FVector3 m_Normal;
	Elite::FPoint3 m_Center;

	Elite::FVector3 m_EdgeA;
	Elite::FVector3 m_EdgeB;
	Elite::FVector3 m_EdgeC;
};

