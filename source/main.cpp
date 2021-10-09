//External includes
#include "vld.h"
#include "SDL.h"
#include "SDL_surface.h"
#undef main

//Standard includes
#include <iostream>

//Project includes
#include "ETimer.h"
#include "ERenderer.h"
#include "SceneGraph.h"
#include "LightManager.h"
#include "MaterialManager.h"
#include "MeshReader.h"

void ShutDown(SDL_Window* pWindow)
{
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}

void SetupScenes(std::vector<int>& transformIndices)
{
	//Materials
	Material* pLambertRed{ new LambertMaterial(0.5f, {1.f,0.f,0.f}) };
	Material* pLambertGreen{ new LambertMaterial(0.5f, {0.f,1.f,0.f}) };
	Material* pLambertGray{ new LambertMaterial(0.5f, { .5f,.5f,0.5f }) };
	Material* pLambertPhongLightGreen{ new LambertPhongMaterial(1.f, {0.49f, 1.f, 0.f}, 1.f, 60) };
	Material* pLambertCookTerranceDielectricRough{ new LambertCookTorranceMaterial(false, 1.0, Material::GetColorForMetal(Material::BaseMaterial::Dielectric)) };
	Material* pLambertCookTerranceDielectricHalfRough{ new LambertCookTorranceMaterial(false, .6f, Material::GetColorForMetal(Material::BaseMaterial::Dielectric)) };
	Material* pLambertCookTerranceDielectricSmooth{ new LambertCookTorranceMaterial(false, .1f, Material::GetColorForMetal(Material::BaseMaterial::Dielectric)) };
	Material* pLambertCookTerranceSilverRough{ new LambertCookTorranceMaterial(true, 1.f, Material::GetColorForMetal(Material::BaseMaterial::Silver)) };
	Material* pLambertCookTerranceGoldHalfRough{ new LambertCookTorranceMaterial(true, .5f, Material::GetColorForMetal(Material::BaseMaterial::Gold)) };
	Material* pLambertCookTerranceTitaniumSmooth{ new LambertCookTorranceMaterial(true, .1f, Material::GetColorForMetal(Material::BaseMaterial::Titanium)) };

	MaterialManager::GetInstance()->AddMaterial(pLambertRed);
	MaterialManager::GetInstance()->AddMaterial(pLambertGreen);
	MaterialManager::GetInstance()->AddMaterial(pLambertGray);
	MaterialManager::GetInstance()->AddMaterial(pLambertPhongLightGreen);
	MaterialManager::GetInstance()->AddMaterial(pLambertCookTerranceDielectricRough);
	MaterialManager::GetInstance()->AddMaterial(pLambertCookTerranceDielectricHalfRough);
	MaterialManager::GetInstance()->AddMaterial(pLambertCookTerranceDielectricSmooth);
	MaterialManager::GetInstance()->AddMaterial(pLambertCookTerranceSilverRough);
	MaterialManager::GetInstance()->AddMaterial(pLambertCookTerranceGoldHalfRough);
	MaterialManager::GetInstance()->AddMaterial(pLambertCookTerranceTitaniumSmooth);

	//Scene 1
	SceneGraph::GetInstance()->SetIsScene0Active(true);
	SceneGraph::GetInstance()->AddObject(new Plane({ 0.f, 0.f, 0.f }, pLambertGray, { 0.f, 1.f, 0.f }, Object::Cullmode::BackFaceCulling));
	SceneGraph::GetInstance()->AddObject(new Plane({ 0.f, 0.f, -5.f }, pLambertGray, { 0.f, 0.f, .75f }, Object::Cullmode::BackFaceCulling));
	SceneGraph::GetInstance()->AddObject(new Plane({ -5.f, 0.f, 0.f }, pLambertGray, { 1.f, 0.f, 0.f }, Object::Cullmode::BackFaceCulling));
	SceneGraph::GetInstance()->AddObject(new Plane({ 5.f, 0.f, 0.f }, pLambertGray, { -1.f, 0.f, 0.f }, Object::Cullmode::BackFaceCulling));

	float yMetals{ 1.f };
	float yDielectrics{ 3.2f };
	SceneGraph::GetInstance()->AddObject(new Sphere({ -2.5f, yDielectrics, 0.f }, pLambertCookTerranceDielectricRough, 1.f));
	SceneGraph::GetInstance()->AddObject(new Sphere({ 0.f, yDielectrics, 0.f }, pLambertCookTerranceDielectricHalfRough, 1.f));
	SceneGraph::GetInstance()->AddObject(new Sphere({ 2.5f, yDielectrics, 0.f }, pLambertCookTerranceDielectricSmooth, 1.f));
	SceneGraph::GetInstance()->AddObject(new Sphere({ -2.5f, yMetals, 0.f }, pLambertCookTerranceSilverRough, 1.f));
	SceneGraph::GetInstance()->AddObject(new Sphere({ 0.f, yMetals, 0.f }, pLambertCookTerranceGoldHalfRough, 1.f));
	SceneGraph::GetInstance()->AddObject(new Sphere({ 2.5f, yMetals, 0.f }, pLambertCookTerranceTitaniumSmooth, 1.f, Object::Cullmode::NoCulling));

	int i0 = SceneGraph::GetInstance()->AddObject(new Triangle({ -0.75f, 1.5f, 0 }, { -0.75f, 0, 0 }, { 0.75f, 0, 0 }, pLambertPhongLightGreen, Object::Cullmode::FrontFaceCulling));
	int i1 = SceneGraph::GetInstance()->AddObject(new Triangle({ -0.75f, 1.5f, 0 }, { -0.75f, 0, 0 }, { 0.75f, 0, 0 }, pLambertPhongLightGreen, Object::Cullmode::BackFaceCulling));
	int i2 = SceneGraph::GetInstance()->AddObject(new Triangle({ -0.75f, 1.5f, 0 }, { -0.75f, 0, 0 }, { 0.75f, 0, 0 }, pLambertPhongLightGreen, Object::Cullmode::NoCulling));
	transformIndices.push_back(i0);
	transformIndices.push_back(i1);
	transformIndices.push_back(i2);

	//Scene 2
	SceneGraph::GetInstance()->SetIsScene0Active(false);
	SceneGraph::GetInstance()->AddObject(new Plane({ 0.f, 0.f, 0.f }, pLambertGray, { 0.f, 1.f, 0.f }, Object::Cullmode::BackFaceCulling));
	SceneGraph::GetInstance()->AddObject(new Plane({ 0.f, 0.f, -5.f }, pLambertGray, { 0.f, 0.f, .75f }, Object::Cullmode::BackFaceCulling));
	SceneGraph::GetInstance()->AddObject(new Plane({ -5.f, 0.f, 0.f }, pLambertGray, { 1.f, 0.f, 0.f }, Object::Cullmode::BackFaceCulling));
	SceneGraph::GetInstance()->AddObject(new Plane({ 5.f, 0.f, 0.f }, pLambertGray, { -1.f, 0.f, 0.f }, Object::Cullmode::BackFaceCulling));

	try
	{
		Object* bunny{ MeshReader::ReadObjFile("lowpoly_bunny.obj", pLambertPhongLightGreen) };
		if (bunny)
		{
			SceneGraph::GetInstance()->AddObject(bunny);
			bunny->Transform(Elite::MakeTranslation(Elite::FVector3{ 0.f,1.f,0.f }));
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Something went wrong whilst reading the bunny" << '\n';
		std::cout << e.what() << '\n';
	}
	//Lights
	LightManager::GetInstance()->AddLight(new PointLight(10, { 0,5,-2.f }, { 1,1,1 }));
	LightManager::GetInstance()->AddLight(new PointLight(10, { 0,3.f,5 }, { 1,1,1 }));
	LightManager::GetInstance()->AddLight(new DirectionalLight(1, { -1.f, 1.f, 0.f }, { 0.8f,0.8f,0.8f }));

}

void PrintControls()
{
	std::cout << "---- Controls ----" << '\n';
	std::cout << "Move left:     A" << '\n';
	std::cout << "Move right:    D" << '\n';
	std::cout << "Move forward:  W" << '\n';
	std::cout << "Move backward: S" << '\n';
	std::cout << "Move up:       E" << '\n';
	std::cout << "Move down:     Q" << '\n';
	std::cout << '\n';
	std::cout << "Increase FOV:  Left-Arrow" << '\n';
	std::cout << "Decrease FOV:  Right-Arrow" << '\n';
	std::cout << '\n';
	std::cout << "Take screenshot:	X" << '\n';
	std::cout << "Disable hard shadows:   Z" << '\n';
	std::cout << '\n';
	std::cout << "Toggle Irradiance:         T" << '\n';
	std::cout << "Toggle BRDF:		   Y" << '\n';
	std::cout << "Toggle Directional light:  J" << '\n';
	std::cout << "Toggle 1st Point light:    K" << '\n';
	std::cout << "Toggle 2nd Point light:    L" << '\n';
	std::cout << '\n';
	std::cout << "Toggle scene:    ENTER" << '\n';
	std::cout << "---- Mouse ----" << '\n';
	std::cout << "Left mouse (up/down):		Forward / Backward" << '\n';
	std::cout << "Left mouse (left/right):	Rotate camera left/right" << '\n';
	std::cout << "Right mouse:			Rotate camera" << '\n';
	std::cout << "Left AND Right mouse:		Move up/down" << '\n';
}

int main(int argc, char* args[])
{
	//Unreferenced parameters
	(void)argc;
	(void)args;

	//Create window + surfaces
	SDL_Init(SDL_INIT_VIDEO);

	const uint32_t width = 640;
	const uint32_t height = 480;
	SDL_Window* pWindow = SDL_CreateWindow(
		"RayTracer - Jonas De Ridder",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, 0);

	if (!pWindow)
		return 1;

	//Initialize "framework"
	Elite::Timer* pTimer = new Elite::Timer();
	Elite::Renderer* pRenderer = new Elite::Renderer(pWindow);
	Camera* pCamera = new Camera(float(width), float(height), { 0,3.5f,12 }, {0,0,1}, float(E_PI_DIV_4));
	

	//Scene vars
	float turningAngle{};
	const float turningSpeed{ 2.5f };
	bool renderScene0{ true };
	Elite::FMatrix4 translate0{ Elite::MakeTranslation(Elite::FVector3{-2.5f,5.f, 0.f}) };
	Elite::FMatrix4 translate1{ Elite::MakeTranslation(Elite::FVector3{0,5.f, 0.f}) };
	Elite::FMatrix4 translate2{ Elite::MakeTranslation(Elite::FVector3{2.5f,5.f, 0.f}) };

	std::vector<int> transformIndices{};
	SetupScenes(transformIndices);
	
	SceneGraph::GetInstance()->SetIsScene0Active(renderScene0);

	PrintControls();

	//Start loop
	pTimer->Start();
	float printTimer = 0.f;
	bool isLooping = true;
	bool takeScreenshot = false;
	while (isLooping)
	{
		//--------- Get input events ---------
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				isLooping = false;
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_X:
					takeScreenshot = true;
					break;
				case SDL_SCANCODE_J:
					pRenderer->m_IsDirectionalLightEnabled = !pRenderer->m_IsDirectionalLightEnabled;
					std::cout << std::boolalpha << "Directional light: " << pRenderer->m_IsDirectionalLightEnabled << '\n';
					break;
				case SDL_SCANCODE_K:
					pRenderer->m_IsFirstPointLightEnabled = !pRenderer->m_IsFirstPointLightEnabled;
					std::cout << std::boolalpha << "First Point light: " << pRenderer->m_IsFirstPointLightEnabled << '\n';
					break;
				case SDL_SCANCODE_L:
					pRenderer->m_IsSecondPointLightEnabled = !pRenderer->m_IsSecondPointLightEnabled;
					std::cout << std::boolalpha << "Second Point light: " << pRenderer->m_IsSecondPointLightEnabled << '\n';
					break;
				case SDL_SCANCODE_Z:
					pRenderer->m_IsHardShadowsEnabled = !pRenderer->m_IsHardShadowsEnabled;
					std::cout << std::boolalpha << "Hard shadows: " << pRenderer->m_IsHardShadowsEnabled << '\n';
					break;
				case SDL_SCANCODE_T:
					std::cout << "Toggle Irradiance" << '\n';
					//Toggle Irradiance bit
					pRenderer->m_LightingMode = Elite::Renderer::LightingMode(int(pRenderer->m_LightingMode) ^ int(Elite::Renderer::LightingMode::IRRADIANCE));
					break;
				case SDL_SCANCODE_Y:
					std::cout << "Toggle BRDF" << '\n';
					//Toggle BRDF bit
					pRenderer->m_LightingMode = Elite::Renderer::LightingMode(int(pRenderer->m_LightingMode) ^ int(Elite::Renderer::LightingMode::BRDF));
					break;
				case SDL_SCANCODE_RETURN:
				case SDL_SCANCODE_RETURN2:
					std::cout << "Toggling scene" << '\n';
					renderScene0 = !renderScene0;
					SceneGraph::GetInstance()->SetIsScene0Active(renderScene0);
					break;
				}
				break;
			}
		}

		//--------- Update --------
		if (renderScene0)
		{
			turningAngle += turningSpeed * pTimer->GetElapsed();
			Elite::FMatrix4 rot{ Elite::MakeRotationY(turningAngle) };
			for (int i : transformIndices)
			{
				Object* pObj{ SceneGraph::GetInstance()->GetObjectAt(i) };
				Elite::FMatrix4 transform{};
				if (i == 10) transform = translate0 * rot;
				if (i == 11) transform = translate1 * rot;
				if (i == 12) transform = translate2 * rot;

				if (pObj) pObj->Transform(transform);
			}
		}
		
		//--------- Render ---------
		pCamera->Move(pTimer->GetElapsed());
		pRenderer->Render(pCamera);

		//--------- Timer ---------
		pTimer->Update();
		printTimer += pTimer->GetElapsed();
		if (printTimer >= 1.f)
		{
			printTimer = 0.f;
			std::cout << "FPS: " << pTimer->GetFPS() << std::endl;
		}

		//Save screenshot after full render
		if (takeScreenshot)
		{
			if (!pRenderer->SaveBackbufferToImage())
				std::cout << "Screenshot saved!" << std::endl;
			else
				std::cout << "Something went wrong. Screenshot not saved!" << std::endl;
			takeScreenshot = false;
		}
	}
	pTimer->Stop();

	//Shutdown "framework"
	delete pRenderer;
	delete pTimer;
	delete pCamera;
	delete SceneGraph::GetInstance();
	delete LightManager::GetInstance();
	delete MaterialManager::GetInstance();

	ShutDown(pWindow);
	return 0;
}