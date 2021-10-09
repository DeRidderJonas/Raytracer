#pragma once

#include "EMath.h"
#include "ERGBColor.h"

struct Ray final
{
	Ray(const Elite::FPoint3& origin, const Elite::FVector3& direction = {0.f,0.f,-1.f});
	~Ray() = default;

	//Members
	Elite::FPoint3 m_Origin{}; //Screen space
	Elite::FVector3 m_Direction{0,0,-1};

	//Methods
	bool isValidTValue(float t) const;
	void SetMaxTValue(float value);
private:
	float tMin = 0.0001f;
	float tMax = FLT_MAX;
};


struct HitRecord
{
	Elite::FPoint3 hitPoint;
	Elite::FVector3 normal;
	float tValue;
	Elite::RGBColor color;
};
