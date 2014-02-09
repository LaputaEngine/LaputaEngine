#include "LptaTexture.h"

namespace lpta
{

LptaTexture::LptaTexture(ID id, const string &filename, const DATA data, 
        float alpha, const COLOR_KEYS &colorKeys) :
        LptaResource(id), filename(filename), data(data), alpha(alpha), colorKeys(colorKeys)
{
}

LptaTexture::~LptaTexture(void)
{
}

}