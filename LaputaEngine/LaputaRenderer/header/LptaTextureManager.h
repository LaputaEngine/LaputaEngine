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
public:
    LptaTextureManager(void);
    ~LptaTextureManager(void);

    static TEXTURE_PTR CreateNullResource(LptaTexture::TEXTURE_ID, LptaTextureManager *const manager);
};

}

#endif