#include "MaterialManager.h"

MaterialManager* MaterialManager::m_Instance{ nullptr };

MaterialManager* MaterialManager::GetInstance()
{
    if (m_Instance == nullptr) m_Instance = new MaterialManager();

    return m_Instance;
}

MaterialManager::~MaterialManager()
{
    for (Material* pMaterial : m_Materials)
    {
        delete pMaterial;
    }
}

void MaterialManager::AddMaterial(Material* pMaterial)
{
    m_Materials.push_back(pMaterial);
}

const std::vector<Material*>& MaterialManager::GetMaterials() const
{
    return m_Materials;
}




