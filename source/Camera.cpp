#include "Camera.h"
#include "SpaceConverter.h"
#include "SDL.h"
#include "EMathUtilities.h"
#include <iostream>

Camera::Camera(float screenWidth, float screenHeight, const Elite::FPoint3& position, const Elite::FVector3& forward, float FOVAngle)
	: m_ScreenWidth{screenWidth}
	, m_ScreenHeight{screenHeight}
	, m_AspectRatio{screenWidth/screenHeight}
	, m_Position{position}
	, m_Forward{forward}
	, m_FOVAngle{FOVAngle}
	, m_FOV{}
	, m_MousePos{}
	, m_AngleX{0.f}
	, m_AngleY{0.f}
	, m_ONB{}
{
}

Elite::FPoint3 Camera::GetPostion() const
{
	return m_Position;
}

Elite::FVector3 Camera::GetForward() const
{
	return m_Forward;
}

Elite::FPoint3 Camera::GetCameraSpace(float row, float col) const
{
	Elite::FPoint3 space{ SpaceConverter::ToScreenSpace(row, col, m_ScreenHeight, m_ScreenWidth) };
	space.x *= m_AspectRatio * m_FOV;
	space.y *= m_FOV;
	space.z = -1.f;

	return space;
}

void Camera::UpdateFOV()
{
	m_FOV = float(tan(m_FOVAngle / 2.f));
}

void Camera::SetScreen(float width, float height)
{
	m_ScreenWidth = width;
	m_ScreenHeight = height;
	m_AspectRatio = width / height;
}

const Elite::FMatrix4& Camera::GetONB() const
{
	return m_ONB;
}

void Camera::Move(float elapsedSec)
{
	float moveSpeed{ 2.f };
	float FOVAngleSpeed{ 3.f };
	float cameraAngleSpeed{ 1/100.f };
	const Uint8* pKeysStates = SDL_GetKeyboardState(nullptr);
	

	//Movement
	if (pKeysStates[SDL_SCANCODE_W])
	{
		m_Position += -moveSpeed * elapsedSec * GetLocalForward();
	}
	if (pKeysStates[SDL_SCANCODE_S])
	{
		m_Position += moveSpeed * elapsedSec * GetLocalForward();
	}
	if (pKeysStates[SDL_SCANCODE_A])
	{
		Elite::FVector3 sideways{ Elite::Cross(GetLocalForward(), {0,1.f,0}) };
		m_Position += moveSpeed * elapsedSec * sideways;
	}
	if (pKeysStates[SDL_SCANCODE_D])
	{
		Elite::FVector3 sideways{ Elite::Cross(GetLocalForward(), {0,1.f,0}) };
		m_Position += -moveSpeed * elapsedSec * sideways;
	}
	if (pKeysStates[SDL_SCANCODE_Q])
	{
		Elite::FVector3 vertical{ Elite::Cross(GetLocalForward(), {1.f,0,0}) };
		m_Position += -moveSpeed * elapsedSec * vertical;
	}
	if (pKeysStates[SDL_SCANCODE_E])
	{
		Elite::FVector3 vertical{ Elite::Cross(GetLocalForward(), {1.f,0,0}) };
		m_Position += moveSpeed * elapsedSec * vertical;
	}

	//FOV
	if (pKeysStates[SDL_SCANCODE_LEFT])
	{
		if(m_FOVAngle - FOVAngleSpeed * elapsedSec > 0.f) m_FOVAngle += -FOVAngleSpeed * elapsedSec;
	}
	if (pKeysStates[SDL_SCANCODE_RIGHT])
	{
		if(double(m_FOVAngle) + double(FOVAngleSpeed) * double(elapsedSec) < E_PI) m_FOVAngle += FOVAngleSpeed * elapsedSec;
	}

	//Mouse movement
	int x{}, y{};
	auto mouseButton = SDL_GetMouseState(&x, &y);

	if (mouseButton == SDL_BUTTON(SDL_BUTTON_RIGHT) || mouseButton == SDL_BUTTON(SDL_BUTTON_LEFT) || mouseButton == 5)
	{
		if (m_MousePos.x != 0 && m_MousePos.y != 0)
		{
			if (mouseButton == 5)
			{
				Elite::FVector3 vertical{ Elite::Cross(GetLocalForward(), {1.f,0,0}) };
				m_Position += (m_MousePos.y - y > 0 ? 1 : -1) * moveSpeed * elapsedSec * vertical;
			}
			else
			{
				m_AngleX -= (m_MousePos.x - x) * cameraAngleSpeed; //Rot over Y

				if (mouseButton == SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					m_Position += (m_MousePos.y - y > 0 ? 1 : -1) * moveSpeed * elapsedSec * GetLocalForward();
				}
				else m_AngleY -= (m_MousePos.y - y) * cameraAngleSpeed; //Rot over X
			}
		}
		
		//Update mouse pos to current pos
		m_MousePos.x = float(x);
		m_MousePos.y = float(y);
	}
	else
	{
		//if no mouse button held, clear mouse pos
		m_MousePos.x = 0.f;
		m_MousePos.y = 0.f;
	}

	UpdateONB();
}

void Camera::UpdateONB()
{
	const Elite::FVector3 forward{ GetLocalForward() };
	Elite::FVector3 worldUp{ 0,1,0 };
	Elite::FVector3 right{ Elite::Cross(worldUp, forward) };
	Elite::Normalize(right);
	Elite::FVector3 up{ Elite::Cross(forward, right) };
	Elite::Normalize(up);

	m_ONB = Elite::FMatrix4(Elite::FVector4{ right }, Elite::FVector4{ up }, Elite::FVector4{ forward }, Elite::FVector4{ m_Position });
	m_ONB.data[3][3] = 1;
}

const Elite::FVector3 Camera::GetLocalForward() const
{
	Elite::FVector3 localForward{ m_Forward };
	localForward = Elite::MakeRotationX(m_AngleY) * localForward;
	localForward = Elite::MakeRotationY(m_AngleX) * localForward;

	return localForward;
}
