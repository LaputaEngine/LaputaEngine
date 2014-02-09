#include "LptaTextureManager.h"

namespace lpta
{

LptaTextureManager::LptaTextureManager(void)
{
}

LptaTextureManager::~LptaTextureManager(void)
{
}

TEXTURE_PTR LptaTextureManager::CreateNullResource(LptaTexture::TEXTURE_ID id, 
    LptaTextureManager *const manager)
{
    return TEXTURE_PTR(new LptaTexture(
        id,
        "$$DEFAULT_TEXTURE$$",
        LptaTexture::DATA(),
        1.0f,
        LptaTexture::COLOR_KEYS()
    ));
}

}