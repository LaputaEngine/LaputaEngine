#ifndef _LPTASKINMANAGER_H_
#define _LPTASKINMANAGER_H_

#include <memory>
#include "LptaSkin.h"
#include "LptaResourceManager.h"
#include "LptaMaterialManager.h"

namespace lpta
{

class LptaSkinManager : LptaResourceManager<LptaSkin>
{
protected:

public:
    LptaSkinManager(const LptaMaterialManager &materialManager);
    virtual ~LptaSkinManager(void);

    LptaSkin CreateNullResource(void);

    LptaSkin::SKIN_ID AddSkin(LptaMaterial::MATERIAL_ID materialId, bool transparent);
private:
    LptaMaterial defaultMaterial;
};

}

#endif