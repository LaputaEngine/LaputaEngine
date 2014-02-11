#include "LptaTexture.h"

namespace lpta
{

LptaTexture::LptaTexture(ID id, const string &filename, DATA data, 
        float alpha, const COLOR_KEYS &colorKeys) :
        LptaResource(id), data(std::move(data)), filename(filename), alpha(alpha), colorKeys(colorKeys)
{
}

LptaTexture::~LptaTexture(void)
{
}

const string &LptaTexture::GetFilename(void) const
{
    return filename;
}

}