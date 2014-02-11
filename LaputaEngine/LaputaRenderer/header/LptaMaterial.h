#ifndef _LPTAMATERIAL_H_
#define _LPTAMATERIAL_H_

#include <limits>
#include "LptaResource.h"
#include "LptaColor.h"

namespace lpta
{
    
class LptaMaterial : public LptaResource
{
public:
    typedef ID MATERIAL_ID;
public:
    LptaMaterial(void);
    LptaMaterial(MATERIAL_ID id, 
        const LptaColor &diffuse, 
        const LptaColor &ambient, 
        const LptaColor &specular, 
        const LptaColor &emissive, 
        float specularPower);
    ~LptaMaterial(void);

    inline const LptaColor &GetDiffuse(void) const;
    inline const LptaColor &GetAmbient(void) const;
    inline const LptaColor &GetSpecular(void) const;
    inline const LptaColor &GetEmissive(void) const;
    inline float GetSpecularPower(void) const;

    bool operator==(const LptaMaterial &other) const;
    virtual int foo(void) {return 1;}
private:
    LptaColor diffuse;
    LptaColor ambient;
    LptaColor specular;
    LptaColor emissive;
    float specularPower;
};

const LptaColor &LptaMaterial::GetDiffuse(void) const
{
    return diffuse;
}

const LptaColor &LptaMaterial::GetAmbient(void) const
{
    return ambient;
}

const LptaColor &LptaMaterial::GetSpecular(void) const
{
    return specular;
}

const LptaColor &LptaMaterial::GetEmissive(void) const
{
    return emissive;
}

float LptaMaterial::GetSpecularPower(void) const
{
    return specularPower;
}

}

#endif