#pragma once
#include <vector>
#include "Object.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "TriangleMesh.h"

class SceneGraph final
{
public:
	static SceneGraph* GetInstance();
	~SceneGraph();
	SceneGraph(const SceneGraph& other) = delete;
	SceneGraph operator=(const SceneGraph& other) = delete;
	SceneGraph(SceneGraph&& other) = delete;
	SceneGraph operator=(SceneGraph&& other) = delete;
	

	int AddObject(Object* newObject);
	const std::vector<Object*>& GetObjects() const;
	Object* GetObjectAt(int index) const;

	void SetIsScene0Active(bool value);
private:
	SceneGraph() : m_IsScene0Active{false} {};
	static SceneGraph* m_Instance;

	bool m_IsScene0Active;
	std::vector<Object*> m_Objects{};
	std::vector<Object*> m_Objects2{};
};

