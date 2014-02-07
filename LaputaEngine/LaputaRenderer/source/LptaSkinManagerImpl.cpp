#include "LptaSkinManagerImpl.h"

bool LptaSkinManagerImpl::ValidMaterialId(unsigned int materialId) const
{
    return materialId < materials.size();
}

bool LptaSkinManagerImpl::ValidSkinId(unsigned int skinId) const
{
    return skinId < skins.size();
}

bool LptaSkinManagerImpl::ValidTextureId(unsigned int textureId) const
{
    return textureId < textures.size();
}