#ifndef _LPTASKINMANAGER_H_
#define _LPTASKINMANAGER_H_

#include <memory>
#include "LptaSkin.h"
#include "LptaResourceManager.h"
#include "LptaMaterialManager.h"

namespace lpta
{

class LptaSkinManager : LptaResourceManager<LptaSkin, LptaSkinManager>
{
protected:

public:
    LptaSkinManager(const LptaMaterialManager &materialManager);
    virtual ~LptaSkinManager(void);

    static LptaSkin CreateNullResource(LptaSkin::SKIN_ID id, LptaSkinManager *const manager);

private:
    LptaMaterial defaultMaterial;
};

}

#endif