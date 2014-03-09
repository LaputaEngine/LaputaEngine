#include "LptaTexture.h"

namespace lpta
{

LptaTexture::LptaTexture(ID id, const string &filename, DATA data, 
        float alpha, const COLOR_KEYS &colorKeys) :
        LptaResource(id), data(data), filename(filename), alpha(alpha), colorKeys(colorKeys)
{
}

LptaTexture::~LptaTexture(void)
{
}

const string &LptaTexture::GetFilename(void) const
{
    return filename;
}

float LptaTexture::GetAlpha(void) const
{
    return alpha;
}

const LptaTexture::COLOR_KEYS &LptaTexture::GetColorKeys(void) const
{
    return colorKeys;
}

}