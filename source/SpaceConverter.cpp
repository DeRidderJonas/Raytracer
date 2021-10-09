#include "SpaceConverter.h"

Elite::FPoint3 SpaceConverter::ToScreenSpace(float row, float col, float screenheight, float screenwidth)
{
    float x = 2 * ((col + 0.5f) / screenwidth) - 1;
    float y = (1 - 2 * ((row + 0.5f) / screenheight));

    return Elite::FPoint3(x, y);
}
