#include "LptaMaterial.h"
#include "LptaColor.h"
#include "LptaMaterialManager.h"

namespace lpta
{

// purple
const LptaColor LptaMaterialManager::DEFAULT_COLOR = LptaColor(0.5f, 0.0f, 1.0f, 1.0f);

LptaMaterialManager::LptaMaterialManager(void)
{
}

LptaMaterialManager::~LptaMaterialManager(void)
{
}

LptaMaterial LptaMaterialManager::CreateNullResource(LptaMaterial::MATERIAL_ID id, 
    LptaMaterialManager *const manager)
{
    return LptaMaterial(
        id,
        DEFAULT_COLOR,
        DEFAULT_COLOR,
        DEFAULT_COLOR,
        DEFAULT_COLOR,
        0.0f
    );
}

}