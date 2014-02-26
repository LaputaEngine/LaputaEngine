#include "LptaD3DUtils.h"
#include "resources/errors/ShaderCompileFail.h"
#include "resources/LptaD3DVertexShaderManager.h"

namespace lpta_d3d
{

const std::string LptaD3DVertexShaderManager::defaultShaderProgram = 
    "vs.1.1\n"
    "dcl_position0  v0\n"
    "dcl_normal0    v3\n"
    "dcl_texcoord0  v6\n"
    "dp4 oPos.x, v0, c0\n"
    "dp4 oPos.y, v0, c1\n"
    "dp4 oPos.z, v0, c2\n"
    "dp4 oPos.w, v0, c3\n"
    "mov oD0, c4\n"
    "mov oT0, v6\n";

LptaD3DVertexShaderManager::LptaD3DVertexShaderManager(LPDIRECT3DDEVICE9 d3ddev) : d3ddev(d3ddev)
{
    LPDIRECT3DVERTEXSHADER9 defaultShader = LoadAndCompile(defaultShaderProgram);
    this->SetNullResource(LptaD3DVertexShader(GetNextId(), defaultShader));
}

LptaD3DVertexShaderManager::~LptaD3DVertexShaderManager(void)
{
    for (auto resource : resources) {
        resource.second.GetVertexShader()->Release();
    }
    resources.clear();
}

HRESULT LptaD3DVertexShaderManager::D3DCreateShader(DWORD *shader, LPDIRECT3DVERTEXSHADER9 *handle)
{
    return d3ddev->CreateVertexShader(shader, handle);
}

}