#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(const std::vector<Elite::FPoint3>& vertices, const std::vector<int>& indexBuffer, Material* pMaterial, Cullmode cullmode)
	: Object{ {}, pMaterial, cullmode }
	, m_Vertices{vertices}
	, m_VerticesWorld{vertices}
	, m_IndexBuffer{indexBuffer}
{
}

void TriangleMesh::Transform(const Elite::FMatrix4& transform)
{
	for (size_t i = 0; i < m_Vertices.size(); ++i)
	{
		m_VerticesWorld[i] = Elite::FPoint3{ transform * Elite::FPoint4{m_Vertices[i]} };
	}
}

bool TriangleMesh::Hit(const Ray& ray, HitRecord& hitRecord) const
{
	hitRecord.tValue = FLT_MAX;
	HitRecord currHR{};

	for (size_t i = 0; i < m_IndexBuffer.size(); i += 3)
	{
		int i0 = m_IndexBuffer[i];
		int i1 = m_IndexBuffer[i + 1];
		int i2 = m_IndexBuffer[i + 2];

		Triangle triangle{ m_VerticesWorld[i0], m_VerticesWorld[i1], m_VerticesWorld[i2], m_Material, m_Cullmode };

		if (triangle.Hit(ray, currHR) && currHR.tValue < hitRecord.tValue)
		{
			hitRecord = currHR;
		}
	}

	return ray.isValidTValue(hitRecord.tValue);
}