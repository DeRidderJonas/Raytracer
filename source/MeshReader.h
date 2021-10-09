#pragma once
#include "TriangleMesh.h"
#include <string>

class MeshReader final
{
public:
	static TriangleMesh* ReadObjFile(const std::string& fileName, Material* pMaterial, Object::Cullmode cullmode = Object::Cullmode::NoCulling);
private:
	static bool IsVertex(const std::string& line, Elite::FPoint3& vertex);
	static bool IsFace(const std::string& line, int& i0, int& i1, int& i2);
};

