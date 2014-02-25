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
    LPDIRECT3DVERTEXSHADER9 defaultShader = LoadAndCompileShader(defaultShaderProgram);
    this->SetNullResource(LptaD3DVertexShader(GetNextId(), defaultShader));
}

LptaD3DVertexShaderManager::~LptaD3DVertexShaderManager(void)
{
    this->resources.clear();
}

// todo refactor, we can do this a lot cleaner after moving it away from the d3d device class
LPDIRECT3DVERTEXSHADER9 LptaD3DVertexShaderManager::LoadShader(void *data)
{
    LPDIRECT3DVERTEXSHADER9 shader;
    HRESULT result = d3ddev->CreateVertexShader(static_cast<DWORD *>(data), &shader);
    // todo save shader program pointer somewhere
    if (SUCCEEDED(result)) {
        return shader;
    }
    else {
        throw ShaderCompileFail();
    }
}

LPDIRECT3DVERTEXSHADER9 LptaD3DVertexShaderManager::LoadShaderFromFile(const std::string &filename)
{
    HANDLE fileHandle = CreateFile(lpta_d3d_utils::ToWChar(filename).c_str(), GENERIC_READ, 
        false, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (INVALID_HANDLE_VALUE == fileHandle) {
        throw ShaderCompileFail();
    }
    
    HANDLE fileMemMap = CreateFileMapping(fileHandle, 0, PAGE_READONLY, 0, 0, 0);
    void *fileMapView = MapViewOfFile(fileMemMap, FILE_MAP_READ, 0, 0, 0);
    LPDIRECT3DVERTEXSHADER9 shader = LoadShader(fileMapView);
    
    UnmapViewOfFile(fileMapView);   
    CloseHandle(fileMemMap);
    CloseHandle(fileHandle);

    return shader;
}

LPDIRECT3DVERTEXSHADER9 LptaD3DVertexShaderManager::LoadAndCompileShader(std::string shader)
{
    LPD3DXBUFFER compiled;
    LPD3DXBUFFER errorMsg;
    HRESULT assembleResult = D3DXAssembleShader(
        shader.c_str(), shader.length() , NULL, NULL, 0, &compiled, &errorMsg); 

    if (SUCCEEDED(assembleResult)) {
        return LoadShader(compiled->GetBufferPointer());
    }
    else {
        throw ShaderCompileFail();
    }
}

LPDIRECT3DVERTEXSHADER9 LptaD3DVertexShaderManager::LoadAndCompileShaderFromFile(const std::string &filename)
{
    LPD3DXBUFFER compiled;
    LPD3DXBUFFER errorMsg;
    HRESULT assembleResult = D3DXAssembleShaderFromFileW(
        lpta_d3d_utils::ToWChar(filename).c_str(), NULL, NULL, 0, &compiled, &errorMsg);
    
    if (SUCCEEDED(assembleResult)) {
        return LoadShader(compiled->GetBufferPointer());
    }
    else {
        throw ShaderCompileFail();
    }
}

}