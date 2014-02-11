#ifndef _LPTAMATERIALMANAGER_H_
#define _LPTAMATERIALMANAGER_H_

#include <memory>
#include "LptaMaterial.h"
#include "LptaResourceManager.h"

namespace lpta
{

class LptaMaterialManager : public LptaResourceManager<LptaMaterial>
{
public:
    LptaMaterialManager(void);
    virtual ~LptaMaterialManager(void);

    LptaMaterial CreateNullResource(void);

    LptaMaterial::MATERIAL_ID AddOrRetrieveMaterial(const LptaColor &diffuse, 
        const LptaColor &ambient, 
        const LptaColor &specular, 
        const LptaColor &emissive, 
        float specularPower);

protected:
    static const LptaColor DEFAULT_COLOR;

};

}

#endif