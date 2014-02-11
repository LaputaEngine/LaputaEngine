#include "LptaMaterial.h"
#include "LptaColor.h"
#include "LptaMaterialManager.h"

namespace lpta
{

// purple
const LptaColor LptaMaterialManager::DEFAULT_COLOR = LptaColor(0.5f, 0.0f, 1.0f, 1.0f);

LptaMaterialManager::LptaMaterialManager(void)
{
    SetNullResource(CreateNullResource());
}

LptaMaterialManager::~LptaMaterialManager(void)
{
}

LptaMaterial LptaMaterialManager::CreateNullResource(void)
{
    return LptaMaterial(
        GetNextId(),
        DEFAULT_COLOR,
        DEFAULT_COLOR,
        DEFAULT_COLOR,
        DEFAULT_COLOR,
        0.0f
    );
}

LptaMaterial::MATERIAL_ID LptaMaterialManager::AddOrRetrieveMaterial(const LptaColor &diffuse, 
        const LptaColor &ambient, 
        const LptaColor &specular, 
        const LptaColor &emissive, 
        float specularPower)
{
    LptaMaterial material(GetNextId(), diffuse, ambient, specular, emissive, specularPower);
    for (RESOURCES::const_iterator mat = resources.begin(); mat != resources.end(); ++mat) {
        const LptaMaterial &candidate = mat->second;
        if (candidate == material) {
            return candidate.GetId();
        }
    }
    return AddResource(material) ? material.GetId() : RetrieveNullResource().GetId();
}

}