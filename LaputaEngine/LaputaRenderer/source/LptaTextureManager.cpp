#include "LptaTextureManager.h"

namespace lpta
{

LptaTextureManager::LptaTextureManager(void)
{
}

LptaTextureManager::~LptaTextureManager(void)
{
}

LptaTexture LptaTextureManager::CreateNullResource(LptaTexture::TEXTURE_ID id, 
    LptaTextureManager *const manager)
{
    return LptaTexture(
        id,
        "$$DEFAULT_TEXTURE$$",
        manager->GenerateDefaultData(),
        1.0f,
        LptaTexture::COLOR_KEYS()
    );
}

}