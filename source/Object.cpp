#include "Object.h"
#include "LambertMaterial.h"
Object::Object(const Elite::FPoint3& origin, Material* pMaterial, Cullmode cullmode)
	: m_Origin{origin}
	, m_OriginWorld{origin}
	, m_Material{pMaterial}
	, m_Cullmode{cullmode}
{
}

void Object::Transform(const Elite::FMatrix4& transform)
{
	m_OriginWorld = Elite::FPoint3{ transform * Elite::FPoint4{m_Origin} };
}

Material* Object::GetMaterial() const
{
	return m_Material;
}

void Object::SetCullmode(Cullmode cullmode)
{
	m_Cullmode = cullmode;
}

void Object::InvertCullmode()
{
	switch (m_Cullmode)
	{
	case Object::Cullmode::BackFaceCulling:
		m_Cullmode = Cullmode::FrontFaceCulling;
		break;
	case Object::Cullmode::FrontFaceCulling:
		m_Cullmode = Cullmode::BackFaceCulling;
		break;
	}
}
