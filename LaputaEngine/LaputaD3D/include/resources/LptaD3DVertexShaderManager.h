#ifndef _LPTAD3DVERTEXSHADERMANAGER_H_
#define _LPTAD3DVERTEXSHADERMANAGER_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "LptaD3DVertexShader.h"
#include "LptaD3DShaderManager.h"

namespace lpta_d3d
{

class LptaD3DVertexShaderManager : 
    public LptaD3DShaderManager<LptaD3DVertexShader, LPDIRECT3DVERTEXSHADER9>
{
public:
    LptaD3DVertexShaderManager(LPDIRECT3DDEVICE9 d3ddev);
    ~LptaD3DVertexShaderManager(void);

protected:
    HRESULT D3DCreateShader(DWORD *shader, LPDIRECT3DVERTEXSHADER9 *handle);

private:
    static const std::string defaultShaderProgram;
    
    LPDIRECT3DDEVICE9 d3ddev;
};

}

#endif