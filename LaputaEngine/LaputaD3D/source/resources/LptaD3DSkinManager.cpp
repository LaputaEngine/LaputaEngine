#include "resources/LptaD3DSkinManager.h"

namespace lpta_d3d
{

LptaD3DSkinManager::LptaD3DSkinManager(const lpta::LptaMaterialManager &materialManager, 
    LPDIRECT3DDEVICE9 d3ddev) : LptaSkinManager(materialManager), d3ddev(d3ddev)
{
}

LptaD3DSkinManager::~LptaD3DSkinManager(void)
{
}

}