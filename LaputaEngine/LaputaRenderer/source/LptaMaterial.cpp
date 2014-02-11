#include "LptaMaterial.h"

namespace lpta
{

LptaMaterial::LptaMaterial(MATERIAL_ID id, 
        const LptaColor &diffuse, 
        const LptaColor &ambient, 
        const LptaColor &specular, 
        const LptaColor &emissive, 
        float specularPower) : 
        LptaResource(id), diffuse(diffuse), ambient(ambient), specular(specular), emissive(emissive), 
        specularPower(specularPower)
{
}

LptaMaterial::~LptaMaterial(void)
{
}

bool LptaMaterial::operator ==(const LptaMaterial &other) const
{
    return ambient == other.ambient &&
        diffuse == other.diffuse &&
        specular == other.specular &&
        emissive == other.emissive &&
        specularPower == other.specularPower;
}

}