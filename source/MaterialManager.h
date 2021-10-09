#pragma once
#include "Material.h"
#include "LambertMaterial.h"
#include "LambertPhongMaterial.h"
#include "LambertCookTorranceMaterial.h"
#include <vector>

class MaterialManager final
{
public:
	static MaterialManager* GetInstance();
	~MaterialManager();

	MaterialManager(const MaterialManager& other) = delete;
	MaterialManager& operator=(const MaterialManager& other) = delete;
	MaterialManager(MaterialManager&& other) = delete;
	MaterialManager& operator=(MaterialManager&& other) = delete;

	void AddMaterial(Material* pMaterial);
	const std::vector<Material*>& GetMaterials() const;
private:
	MaterialManager() {};
	static MaterialManager* m_Instance;

	std::vector<Material*> m_Materials{};
};

