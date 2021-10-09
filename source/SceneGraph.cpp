#include "SceneGraph.h"

SceneGraph* SceneGraph::m_Instance{ nullptr };

SceneGraph::~SceneGraph()
{
    for (Object* obj : m_Objects)
    {
        delete obj;
    }

    for (Object* obj : m_Objects2)
    {
        delete obj;
    }
}

SceneGraph* SceneGraph::GetInstance()
{
    if (m_Instance == nullptr) m_Instance = new SceneGraph();

    return m_Instance;
}

int SceneGraph::AddObject(Object* newObject)
{
    if (m_IsScene0Active)
    {
        m_Objects.push_back(newObject);
        return int(m_Objects.size()) - 1;
    }
    else
    {
        m_Objects2.push_back(newObject);
        return int(m_Objects2.size()) - 1;
    }
}

const std::vector<Object*>& SceneGraph::GetObjects() const
{
    if (m_IsScene0Active) return m_Objects;
    else return m_Objects2;
}

Object* SceneGraph::GetObjectAt(int index) const
{
    if (m_IsScene0Active)
    {
        if (index >= m_Objects.size()) return nullptr;
        return m_Objects[index];
    }
    else 
    {
        if (index >= m_Objects2.size()) return nullptr;
        return m_Objects2[index];
    }
}

void SceneGraph::SetIsScene0Active(bool value)
{
    m_IsScene0Active = value;
}

