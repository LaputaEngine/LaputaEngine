#include "LptaTextureManager.h"

namespace lpta
{

LptaTextureManager::LptaTextureManager(void)
{
}

LptaTextureManager::~LptaTextureManager(void)
{
}

LptaTexture LptaTextureManager::CreateNullResource(void)
{
    return LptaTexture(
        GetNextId(),
        "$$DEFAULT_TEXTURE$$",
        this->GenerateDefaultData(),
        1.0f,
        LptaTexture::COLOR_KEYS()
    );
}

}