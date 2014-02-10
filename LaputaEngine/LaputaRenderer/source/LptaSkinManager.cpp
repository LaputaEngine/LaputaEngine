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

SKIN_PTR LptaSkinManager::CreateNullResource(LptaSkin::SKIN_ID id, LptaSkinManager *const manager)
{
    return SKIN_PTR(new LptaSkin(
        id,
        manager->nullResource->GetId(),
        LptaSkin::SKIN_NON_TRANSPARENT
    ));
}

}