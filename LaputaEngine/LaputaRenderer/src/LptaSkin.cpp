#include <limits>
#include "LptaSkin.h"

namespace lpta
{

const LptaResource::ID LptaSkin::INVALID_TEXTURE_ID = std::numeric_limits<LptaResource::ID>::max();

LptaSkin::LptaSkin(SKIN_ID id, LptaMaterial::MATERIAL_ID materialId, bool transparent) :
    LptaSkin(id, materialId, transparent, TEXTURE_IDS())
{
    for (auto &id : textureIds) {
        id = INVALID_TEXTURE_ID;
    }
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