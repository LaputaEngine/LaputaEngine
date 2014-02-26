#ifndef _LPTAD3DPIXELSHADERMANAGER_H_
#define _LPTAD3DPIXELSHADERMANAGER_H_

#include "LptaD3DShaderManager.h"
#include "LptaResourceManager.h"
#include "LptaD3DPixelShader.h"

namespace lpta_d3d
{

class LptaD3DPixelShaderManager : public LptaD3DShaderManager<LptaD3DPixelShader, 
    LPDIRECT3DPIXELSHADER9>
{
public:
    LptaD3DPixelShaderManager(LPDIRECT3DDEVICE9 d3ddev);
    ~LptaD3DPixelShaderManager(void);

protected:
    template <class ResourceT, class DxT>
    friend class LptaD3DShaderManager;
    HRESULT D3DCreateShader(DWORD *shader, LPDIRECT3DPIXELSHADER9 *handle);

private:
    static const std::string defaultShaderProgram;

    LPDIRECT3DDEVICE9 d3ddev;
};

}

#endif