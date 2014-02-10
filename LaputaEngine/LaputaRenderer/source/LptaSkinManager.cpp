#include "LptaMaterialManager.h"
#include "LptaSkinManager.h"

namespace lpta
{

LptaSkinManager::LptaSkinManager(const LptaMaterialManager &materialManager) : 
    defaultMaterial(materialManager.GetNullResource())
{
}

LptaSkinManager::~LptaSkinManager(void)
{
}

LptaSkin LptaSkinManager::CreateNullResource(LptaSkin::SKIN_ID id, LptaSkinManager *const manager)
{
    return LptaSkin(
        id,
        manager->nullResource.GetId(),
        LptaSkin::SKIN_NON_TRANSPARENT
    );
}

}