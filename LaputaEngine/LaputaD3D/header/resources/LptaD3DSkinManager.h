#ifndef _LPTAD3DSKINMANAGER_H_
#define _LPTAD3DSKINMANAGER_H_

#include <d3d9.h>
#include "LptaMaterialManager.h"
#include "LptaSkinManager.h"

namespace lpta_d3d
{

class LptaD3DSkinManager : lpta::LptaSkinManager
{
public:
    LptaD3DSkinManager(const lpta::LptaMaterialManager &materialManager, LPDIRECT3DDEVICE9 d3ddev);
    ~LptaD3DSkinManager(void);
    
private:
    const LPDIRECT3DDEVICE9 d3ddev;
};

}

#endif