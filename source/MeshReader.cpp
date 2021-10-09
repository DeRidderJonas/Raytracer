#include "MeshReader.h"
#include <fstream>
#include <sstream>
#include <map>

TriangleMesh* MeshReader::ReadObjFile(const std::string& fileName, Material* pMaterial, Object::Cullmode cullmode)
{
	std::ifstream input{ fileName };
	std::string line;

	Elite::FPoint3 vertex{};
	int i0{}, i1{}, i2{};

	std::vector<Elite::FPoint3> vertexBuffer{};
	std::vector<int> indexBuffer{};
	std::map<int, int> duplicateIndices{};

	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			if (IsVertex(line, vertex))
			{
				auto duplicate{ std::find(vertexBuffer.begin(), vertexBuffer.end(), vertex) };
				if (duplicate != vertexBuffer.end())
				{
					//Duplicate found
					int index{ int(std::distance(vertexBuffer.begin(), duplicate)) };
					duplicateIndices.insert({ int(vertexBuffer.size()), index });
				}
				else vertexBuffer.push_back(vertex);
			}
			if (IsFace(line, i0, i1, i2))
			{
				for (const std::pair<int, int>& pair : duplicateIndices)
				{
					if (i0 == pair.first) i0 = pair.second;
					if (i1 == pair.first) i1 = pair.second;
					if (i2 == pair.first) i2 = pair.second;

					if (i0 > pair.first) --i0;
					if (i1 > pair.first) --i1;
					if (i2 > pair.first) --i2;
				}

				indexBuffer.push_back(i0);
				indexBuffer.push_back(i1);
				indexBuffer.push_back(i2);
			}
		}

		return new TriangleMesh(vertexBuffer, indexBuffer, pMaterial, cullmode);
	}
    else return nullptr;
}


bool MeshReader::IsVertex(const std::string& line, Elite::FPoint3& vertex)
{
	std::stringstream ss{ line };
	std::string string;
	std::getline(ss, string, ' ');
	if (string != "v") return false;

	ss >> vertex.x;
	ss >> vertex.y;
	ss >> vertex.z;

	if (ss.fail()) return false;

	return true;
}

bool MeshReader::IsFace(const std::string& line, int& i0, int& i1, int& i2)
{
	std::stringstream ss{ line };
	std::string string;
	std::getline(ss, string, ' ');
	if (string != "f") return false;

	ss >> i0;
	ss >> i1;
	ss >> i2;

	if (ss.fail()) return false;

	--i0;
	--i1;
	--i2;

	return true;
}