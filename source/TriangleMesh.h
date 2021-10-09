#pragma once
#include "Object.h"
#include <vector>
#include "Triangle.h"

class TriangleMesh final : public Object
{
public:
	TriangleMesh(const std::vector<Elite::FPoint3>& vertices, const std::vector<int>& indexBuffer, Material* pMaterial, Cullmode cullmode = Cullmode::NoCulling);
	~TriangleMesh() = default;

	virtual void Transform(const Elite::FMatrix4& transform);
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord) const;
private:
	std::vector<Elite::FPoint3> m_Vertices;
	std::vector<Elite::FPoint3> m_VerticesWorld;

	std::vector<int> m_IndexBuffer;
};

