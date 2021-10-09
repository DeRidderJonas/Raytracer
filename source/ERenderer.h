/*=============================================================================*/
// Copyright 2017-2019 Elite Engine
// Authors: Matthieu Delaere
/*=============================================================================*/
// ERenderer.h: class that holds the surface to render to, does traverse the pixels 
// and traces the rays using a tracer
/*=============================================================================*/
#ifndef ELITE_RAYTRACING_RENDERER
#define	ELITE_RAYTRACING_RENDERER

#include <cstdint>
#include "Camera.h"
#include "Ray.h"
#include "Object.h"


struct SDL_Window;
struct SDL_Surface;

namespace Elite
{
	class Renderer final
	{
	public:
		Renderer(SDL_Window* pWindow);
		~Renderer() = default;

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void Render(Camera* pCamera);
		bool SaveBackbufferToImage() const;

		bool m_IsDirectionalLightEnabled;
		bool m_IsFirstPointLightEnabled;
		bool m_IsSecondPointLightEnabled;
		bool m_IsHardShadowsEnabled;

		enum class LightingMode
		{
			IRRADIANCE = 1,
			BRDF = 2,
			ALL = 3
		};
		LightingMode m_LightingMode;
	private:
		SDL_Window* m_pWindow = nullptr;
		SDL_Surface* m_pFrontBuffer = nullptr;
		SDL_Surface* m_pBackBuffer = nullptr;
		uint32_t* m_pBackBufferPixels = nullptr;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;

		bool HitObjects(const Ray& ray, HitRecord& hitRecord, Object*& objectHit);
		bool HitAnyObject(const Ray& ray);
		void CalculateLightAndShadowEffects(const Ray& ray, HitRecord& hitRecord, Object* objectHit);
	};
}

#endif