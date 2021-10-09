#pragma once
#include <vector>
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"

class LightManager final
{
public:
	static LightManager* GetInstance();
	~LightManager();

	LightManager(const LightManager& other) = delete;
	LightManager operator=(const LightManager& other) = delete;
	LightManager(LightManager&& other) = delete;
	LightManager operator=(LightManager&& other) = delete;

	void AddLight(Light* pLight);
	const std::vector<Light*>& GetLights() const;
private:
	LightManager() {};
	static LightManager* m_Instace;

	std::vector<Light*> m_Lights{};
};

