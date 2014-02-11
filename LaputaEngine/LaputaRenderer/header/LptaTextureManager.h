#ifndef _LPTATEXTUREMANAGER_H_
#define _LPTATEXTUREMANAGER_H_

#include <string>
#include "LptaTexture.h"
#include "LptaResourceManager.h"

namespace lpta
{

class LptaTextureManager : 
    public LptaResourceManager<LptaTexture>
{
protected:
    static const unsigned long DEFAULT_TEXTURE_COLOR = 0xFF7F00FF;
    static const unsigned int DEFAULT_TEXTURE_WIDTH = 64;
    static const unsigned int DEFAULT_TEXTURE_HEIGHT = DEFAULT_TEXTURE_WIDTH;

public:
    LptaTextureManager(void);
    ~LptaTextureManager(void);

    LptaTexture CreateNullResource(void);

    virtual LptaTexture::TEXTURE_ID AddorRetrieveTexture(const std::string &filename, bool transparent, float alpha,
        const LptaTexture::COLOR_KEYS &colorKeys) = 0;

protected:
    virtual LptaTexture::DATA GenerateDefaultData(void) = 0;

};

}

#endif