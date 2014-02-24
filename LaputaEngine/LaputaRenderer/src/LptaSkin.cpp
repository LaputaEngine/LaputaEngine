#include "LptaSkin.h"

namespace lpta
{

LptaSkin::LptaSkin(SKIN_ID id, LptaMaterial::MATERIAL_ID materialId, bool transparent) :
    LptaSkin(id, materialId, transparent, TEXTURE_IDS())
{
}

LptaSkin::LptaSkin(SKIN_ID id, LptaMaterial::MATERIAL_ID materialId, bool transparent,
        const TEXTURE_IDS &textureIds) : LptaResource(id), transparent(transparent), materialId(materialId),
        textureIds(textureIds)
{
}

LptaSkin::~LptaSkin(void)
{
}

}