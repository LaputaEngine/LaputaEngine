#include "resources/LptaD3DPixelShaderManager.h"

namespace lpta_d3d
{

const std::string LptaD3DPixelShaderManager::defaultShaderProgram = 
    "ps.1.1\n"
    "tex t0\n"
    "mul r0, v0, t0\n";

LptaD3DPixelShaderManager::LptaD3DPixelShaderManager(LPDIRECT3DDEVICE9 d3ddev) : d3ddev(d3ddev)
{
    LPDIRECT3DPIXELSHADER9 defaultShader = LoadAndCompile(defaultShaderProgram);
    this->SetNullResource(LptaD3DPixelShader(GetNextId(), defaultShader));
}

LptaD3DPixelShaderManager::~LptaD3DPixelShaderManager(void)
{
    for (auto resource : resources) {
        resource.second.GetPixelShader()->Release();
    }
    resources.clear();
}

HRESULT LptaD3DPixelShaderManager::D3DCreateShader(DWORD *shader, LPDIRECT3DPIXELSHADER9 *handle)
{
    return d3ddev->CreatePixelShader(shader, handle);
}

}