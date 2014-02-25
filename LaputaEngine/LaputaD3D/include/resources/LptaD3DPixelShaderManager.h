#ifndef _LPTAD3DPIXELSHADERMANAGER_H_
#define _LPTAD3DPIXELSHADERMANAGER_H_

#include "LptaResourceManager.h"
#include "LptaD3DPixelShader.h"

namespace lpta_d3d
{

class LptaD3DPixelShaderManager : public lpta::LptaResourceManager<LptaD3DPixelShader>
{
public:
    LptaD3DPixelShaderManager(LPDIRECT3DDEVICE9 d3ddev);
    ~LptaD3DPixelShaderManager(void);

private:
    LPDIRECT3DDEVICE9 d3ddev;
};

}

#endif