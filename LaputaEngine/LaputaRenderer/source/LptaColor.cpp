#include "LptaColor.h"

namespace lpta
{

const float LptaColor::DEFAULT_CHANNEL_VALUE = 1.0f;

LptaColor::LptaColor(void) : LptaColor(DEFAULT_CHANNEL_VALUE, DEFAULT_CHANNEL_VALUE, 
    DEFAULT_CHANNEL_VALUE, DEFAULT_CHANNEL_VALUE)
{
}

LptaColor::LptaColor(float red, float green, float blue, float alpha)
{
    channels[RED] = red;
    channels[GREEN] = green;
    channels[BLUE] = blue;
    channels[ALPHA] = alpha;
}

LptaColor::~LptaColor(void)
{
}

}