#include "LightManager.h"

LightManager* LightManager::m_Instace{ nullptr };

LightManager* LightManager::GetInstance()
{
    if (m_Instace == nullptr) m_Instace = new LightManager();

    return m_Instace;
}

LightManager::~LightManager()
{
    for (Light* pLight : m_Lights)
    {
        delete pLight;
    }
}

void LightManager::AddLight(Light* pLight)
{
    m_Lights.push_back(pLight);
}

const std::vector<Light*>& LightManager::GetLights() const
{
    return m_Lights;
}
