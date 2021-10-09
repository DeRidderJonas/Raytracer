#pragma once
#include "EMath.h"
#include "Ray.h"
#include "Material.h"
class Object
{
public:
	enum class Cullmode
	{
		BackFaceCulling,
		FrontFaceCulling,
		NoCulling
	};
	Object(const Elite::FPoint3& origin, Material* pMaterial, Cullmode cullmode = Cullmode::NoCulling);
	virtual ~Object() = default;

	virtual void Transform(const Elite::FMatrix4& transform);

	//HitRecord.Normal is not normalized
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord) const = 0;
	Material* GetMaterial() const;
	void SetCullmode(Cullmode cullmode);
	void InvertCullmode();
protected:
	Elite::FPoint3 m_Origin;
	Elite::FPoint3 m_OriginWorld;
	Material* m_Material;
	Cullmode m_Cullmode;
};

