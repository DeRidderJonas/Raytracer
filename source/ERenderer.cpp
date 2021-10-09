//External includes
#include "SDL.h"
#include "SDL_surface.h"

//Project includes
#include "ERenderer.h"
#include "ERGBColor.h"
#include "SpaceConverter.h"
#include "SceneGraph.h"
#include "EMath.h"
#include "LightManager.h"

Elite::Renderer::Renderer(SDL_Window * pWindow)
	: m_IsDirectionalLightEnabled{true}
	, m_IsFirstPointLightEnabled{true}
	, m_IsSecondPointLightEnabled{true}
	, m_IsHardShadowsEnabled{true}
	, m_LightingMode{LightingMode::ALL}
{
	//Initialize
	m_pWindow = pWindow;
	m_pFrontBuffer = SDL_GetWindowSurface(pWindow);
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;
}

void Elite::Renderer::Render(Camera* pCamera)
{
	SDL_LockSurface(m_pBackBuffer);

	pCamera->UpdateFOV();
	Elite::FPoint3 cameraPos{ pCamera->GetPostion() };

	//Loop over all the pixels
	for (uint32_t r = 0; r < m_Height; ++r)
	{
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			Elite::FPoint4 sample{ pCamera->GetCameraSpace(float(r), float(c)), cameraPos.z - 1 };
			sample = pCamera->GetONB() * sample;
			Elite::FVector3 direction{ Elite::FPoint3{sample.x, sample.y, sample.z} - cameraPos };
			Ray ray{ pCamera->GetPostion(), direction };

			HitRecord hitRecord{};
			Object* objectHit = nullptr;
			if (HitObjects(ray, hitRecord, objectHit))
			{
				hitRecord.color = {};
				CalculateLightAndShadowEffects(ray, hitRecord, objectHit);
				hitRecord.color.MaxToOne();
				m_pBackBufferPixels[c + (r * m_Width)] = Elite::GetSDL_ARGBColor(hitRecord.color);
			}
			else m_pBackBufferPixels[c + (r * m_Width)] = Elite::GetSDL_ARGBColor(Elite::RGBColor(0, 0, 0));
		}
	}

	SDL_UnlockSurface(m_pBackBuffer);
	SDL_BlitSurface(m_pBackBuffer, 0, m_pFrontBuffer, 0);
	SDL_UpdateWindowSurface(m_pWindow);
}

bool Elite::Renderer::SaveBackbufferToImage() const
{
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}

bool Elite::Renderer::HitObjects(const Ray& ray, HitRecord& hitRecord, Object*& objectHit)
{
	hitRecord.tValue = FLT_MAX;
	HitRecord currHR{};

	const std::vector<Object*>& objects{ SceneGraph::GetInstance()->GetObjects() };

	for (Object* obj : objects)
	{
		if (obj->Hit(ray, currHR) && currHR.tValue < hitRecord.tValue)
		{
			hitRecord = currHR;
			objectHit = obj;
		}
	}

	//If no obj was hit, hitRecord.tValue will be FLT_MAX which is not a valid t value
	return ray.isValidTValue(hitRecord.tValue);
}

bool Elite::Renderer::HitAnyObject(const Ray& ray)
{
	const std::vector<Object*>& objects{ SceneGraph::GetInstance()->GetObjects() };
	HitRecord hr{};
	for (Object* obj : objects)
	{
		obj->InvertCullmode();
		if (obj->Hit(ray, hr))
		{
			obj->InvertCullmode();
			return true;
		}
		obj->InvertCullmode();
	}
	return false;
}

void Elite::Renderer::CalculateLightAndShadowEffects(const Ray& ray, HitRecord& hitRecord, Object* objectHit)
{
	const std::vector<Light*>& lights{ LightManager::GetInstance()->GetLights() };
	const float shadowRayMoveDistance{ 0.05f };

	if (int(m_LightingMode) == 0) return;

	int i{};
	for (Light* pLight : lights)
	{
		++i;
		if (i == 1 && !m_IsFirstPointLightEnabled) continue;
		if (i == 2 && !m_IsSecondPointLightEnabled) continue;
		if (i == 3 && !m_IsDirectionalLightEnabled) continue;


		//Cosine law
		FVector3 lightDirection{ pLight->GetDirection(hitRecord.hitPoint) };
		float dotNormalLightDirection{ Elite::Dot(hitRecord.normal, lightDirection) };
		if (dotNormalLightDirection <= 0) continue;

		//Hard shadows
		if (m_IsHardShadowsEnabled)
		{
			Elite::FPoint3 shadowRayStart{ hitRecord.hitPoint + hitRecord.normal * shadowRayMoveDistance };
			Ray shadowRay{ shadowRayStart, lightDirection };
			shadowRay.SetMaxTValue(1.f);
			if (HitAnyObject(shadowRay)) continue;
		}

		Elite::RGBColor irradiance{1,1,1};
		Elite::RGBColor BRDF{1,1,1};

		//Irradiance bit set
		if ((int(m_LightingMode) & int(LightingMode::IRRADIANCE)))
		{
			irradiance = pLight->GetIrradiance(hitRecord.hitPoint);
		}

		//BRDF bit set
		if (int(m_LightingMode) & int(LightingMode::BRDF))
		{
			BRDF = objectHit->GetMaterial()->Shade(hitRecord, pLight->GetDirection(hitRecord.hitPoint), -ray.m_Direction);
		}

		hitRecord.color += irradiance * BRDF * dotNormalLightDirection;
	}
}

