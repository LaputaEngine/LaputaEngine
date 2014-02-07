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

bool LptaSkinManagerImpl::ColorsEqual(const Lpta::LPTA_COLOR &color0, const Lpta::LPTA_COLOR &color1) const
{
    return color0.red == color1.red &&
        color0.blue == color1.blue &&
        color0.green == color1.green &&
        color0.alpha == color1.alpha;
}

bool LptaSkinManagerImpl::MaterialsEqual(const Lpta::LPTA_MATERIAL &mat0, const Lpta::LPTA_MATERIAL &mat1) const
{
    return ColorsEqual(mat0.ambient, mat1.ambient) &&
        ColorsEqual(mat0.diffuse, mat1.diffuse) &&
        ColorsEqual(mat0.emissive, mat1.emissive) &&
        ColorsEqual(mat0.specular, mat1.specular) &&
        mat0.specularPower == mat1.specularPower;
}
