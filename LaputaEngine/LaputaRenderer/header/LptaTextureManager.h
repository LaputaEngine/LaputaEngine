#ifndef _LPTATEXTUREMANAGER_H_
#define _LPTATEXTUREMANAGER_H_

#include <memory>
#include "LptaTexture.h"
#include "LptaResourceManager.h"

namespace lpta
{

typedef std::shared_ptr<LptaTexture> TEXTURE_PTR;

class LptaTextureManager : public LptaResourceManager<LptaTexture, LptaTextureManager>
{
protected:
    static const unsigned long DEFAULT_TEXTURE_COLOR = 0xFF7F00FF;
    static const unsigned int DEFAULT_TEXTURE_WIDTH = 64;
    static const unsigned int DEFAULT_TEXTURE_HEIGHT = DEFAULT_TEXTURE_WIDTH;

public:
    LptaTextureManager(void);
    ~LptaTextureManager(void);

    static TEXTURE_PTR CreateNullResource(LptaTexture::TEXTURE_ID, LptaTextureManager *const manager);

protected:
    virtual LptaTexture::DATA GenerateDefaultData(void) = 0;
};

}

#endif