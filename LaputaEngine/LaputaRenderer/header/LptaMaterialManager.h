#ifndef _LPTAMATERIALMANAGER_H_
#define _LPTAMATERIALMANAGER_H_

#include <memory>
#include "LptaMaterial.h"
#include "LptaResourceManager.h"

namespace lpta
{

typedef std::shared_ptr<LptaMaterial> MATERIAL_PTR;

class LptaMaterialManager : public LptaResourceManager<LptaMaterial, LptaMaterialManager>
{
public:
    LptaMaterialManager(void);
    virtual ~LptaMaterialManager(void);

    virtual MATERIAL_PTR GetResource(LptaResource::ID id) const;

    static MATERIAL_PTR CreateNullResource(LptaMaterial::MATERIAL_ID, 
        LptaMaterialManager *const manager);

protected:
    static const LptaColor DEFAULT_COLOR;

};

}

#endif