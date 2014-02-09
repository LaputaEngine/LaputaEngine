#ifndef _LPTASKINMANAGER_H_
#define _LPTASKINMANAGER_H_

#include <memory>
#include "LptaSkin.h"
#include "LptaResourceManager.h"
#include "LptaMaterialManager.h"

namespace lpta
{

typedef std::shared_ptr<LptaSkin> SKIN_PTR;

class LptaSkinManager : LptaResourceManager<LptaSkin, LptaSkinManager>
{
protected:

public:
    LptaSkinManager(const LptaMaterialManager &materialManager);
    virtual ~LptaSkinManager(void);

    static SKIN_PTR CreateNullResource(LptaSkin::SKIN_ID id, LptaSkinManager *const manager);

private:
    MATERIAL_PTR defaultMaterial;
};

}

#endif