#pragma once
#include "EMath.h"

class Camera final
{
public:
	Camera(float screenWidth, float screenHeight, const Elite::FPoint3& position = { 0,0,0 }, const Elite::FVector3& forward = {0,0,1}, float FOVAngle = E_PI_DIV_2);
	Elite::FPoint3 GetPostion() const;
	Elite::FVector3 GetForward() const;
	Elite::FPoint3 GetCameraSpace(float row, float col) const;
	void UpdateFOV();
	void SetScreen(float width, float height);
	const Elite::FMatrix4& GetONB() const;
	void Move(float elapsedSec);
private:
	float m_ScreenWidth;
	float m_ScreenHeight;
	float m_AspectRatio;
	float m_FOVAngle; //radians
	float m_FOV;
	Elite::FPoint3 m_Position;
	Elite::FVector3 m_Forward;

	float m_AngleX;
	float m_AngleY;

	Elite::FPoint2 m_MousePos;

	Elite::FMatrix4 m_ONB;

	void UpdateONB();

	const Elite::FVector3 GetLocalForward() const;
};

