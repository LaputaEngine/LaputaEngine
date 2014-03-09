#include "LptaMaterialManager.h"
#include "LptaSkinManager.h"

namespace lpta
{

LptaSkinManager::LptaSkinManager(const LptaMaterialManager &materialManager) : 
    defaultMaterial(materialManager.RetrieveNullResource())
{
    LptaSkin defaultSkin(GetNextId(), defaultMaterial.GetId(), LptaSkin::SKIN_NON_TRANSPARENT);
    SetNullResource(defaultSkin);
}

LptaSkinManager::~LptaSkinManager(void)
{
}

LptaSkin LptaSkinManager::CreateNullResource(void)
{
    return LptaSkin(
        GetNextId(),
        defaultMaterial.GetId(),
        LptaSkin::SKIN_NON_TRANSPARENT
    );
}

LptaSkin::SKIN_ID LptaSkinManager::AddSkin(LptaMaterial::MATERIAL_ID materialId, bool transparent)
{
    LptaSkin skin(GetNextId(), materialId, transparent);
    AddResource(skin);
    return skin.GetId();
}

}