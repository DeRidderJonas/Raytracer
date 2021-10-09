#pragma once
#include "EMath.h"

class SpaceConverter final
{
public:
	static Elite::FPoint3 ToScreenSpace(float row, float col, float screenheight, float screenwidth);
};

