#ifndef _LPTAMATERIALMANAGER_H_
#define _LPTAMATERIALMANAGER_H_

#include <memory>
#include "LptaMaterial.h"
#include "LptaResourceManager.h"

namespace lpta
{

class LptaMaterialManager : public LptaResourceManager<LptaMaterial, LptaMaterialManager>
{
public:
    LptaMaterialManager(void);
    virtual ~LptaMaterialManager(void);

    static LptaMaterial CreateNullResource(LptaMaterial::MATERIAL_ID, 
        LptaMaterialManager *const manager);

protected:
    static const LptaColor DEFAULT_COLOR;

};

}

#endif