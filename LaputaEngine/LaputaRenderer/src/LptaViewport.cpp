#include "LptaViewport.h"

namespace lpta
{

LptaViewport::LptaViewport(void) : LptaViewport(DEFAULT_X, DEFAULT_Y, DEFAULT_WIDTH, DEFAULT_HEIGHT)
{
}

LptaViewport::LptaViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) :
    point({x, y}), dimension({width, height})
{
}

LptaViewport::~LptaViewport(void)
{
}

const VIEWPORT_POINT &LptaViewport::GetPoint(void) const
{
    return point;
}

const VIEWPORT_DIM &LptaViewport::GetDimension(void) const
{
    return dimension;
}

}