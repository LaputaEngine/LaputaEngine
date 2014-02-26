#ifndef _LPTAD3DSHADERMANAGER_H_
#define _LPTAD3DSHADERMANAGER_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "LptaResource.h"
#include "LptaResourceManager.h"
#include "errors/ShaderCompileFail.h"

namespace lpta_d3d
{

template <class ResourceT, class DxT, class DerivedT>
class LptaD3DShaderManager : public lpta::LptaResourceManager<ResourceT>
{
public:
    // todo refine these function definitions
    lpta::LptaResource::ID AddShader(void *data);
    lpta::LptaResource::ID AddShaderFromFile(const std::string &filename);
    lpta::LptaResource::ID CompileAddShader(const std::string &program);
    lpta::LptaResource::ID CompileAddShaderFromFile(const std::string &filename);

protected:
    virtual HRESULT D3DCreateShader(DWORD *shader, DxT *handle) = 0;

    DxT Load(void *program);
    DxT LoadFromFile(const std::string &filename);
    DxT LoadAndCompile(const std::string &program);
    DxT LoadAndCompileFromFile(const std::string &filename);
};

///////////////////////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////
template <class ResourceT, class DxT, class DerivedT>
lpta::LptaResource::ID LptaD3DShaderManager<ResourceT, DxT, DerivedT>::AddShader(void *data)
{
    try {
        ResourceT shader(GetNextId(), Load(data));
        return AddResource(shader)? shader.GetId() : nullResourceId;
    }
    catch (ShaderCompileFail) {
        return nullResourceId;
    }
}

template <class ResourceT, class DxT, class DerivedT>
lpta::LptaResource::ID LptaD3DShaderManager<ResourceT, DxT, DerivedT>::AddShaderFromFile(
    const std::string &filename)
{
    try {
        ResourceT shader(GetNextId(), LoadFromFile(filename));
        return AddResource(shader)? shader.GetId() : nullResourceId;
    }
    catch (ShaderCompileFail) {
        return nullResourceId;
    }
}

template <class ResourceT, class DxT, class DerivedT>
lpta::LptaResource::ID LptaD3DShaderManager<ResourceT, DxT, DerivedT>::CompileAddShader(
    const std::string &program)
{
    try {
        ResourceT shader(GetNextId(), LoadAndCompile(program));
        return AddResource(shader)? shader.GetId() : nullResourceId;
    }
    catch (ShaderCompileFail) {
        return nullResourceId;
    }
}

template <class ResourceT, class DxT, class DerivedT>
lpta::LptaResource::ID LptaD3DShaderManager<ResourceT, DxT, DerivedT>::CompileAddShaderFromFile(
    const std::string &filename)
{
    try {
        ResourceT shader(GetNextId(), LoadAndCompileFromFile(filename));
        return AddResource(shader)? shader.GetId() : nullResourceId;
    }
    catch (ShaderCompileFail) {
        return nullResourceId;
    }
}

///////////////////////////////////////////////////////////////////////////////
// protected
///////////////////////////////////////////////////////////
template <class ResourceT, class DxT, class DerivedT>
DxT LptaD3DShaderManager<ResourceT, DxT, DerivedT>::Load(void *program)
{
    DxT shader;
    HRESULT result = this->D3DCreateShader(static_cast<DWORD *>(program), &shader);
    // todo save shader program pointer somewhere
    if (SUCCEEDED(result)) {
        return shader;
    }
    else {
        throw ShaderCompileFail();
    }
}

template <class ResourceT, class DxT, class DerivedT>
DxT LptaD3DShaderManager<ResourceT, DxT, DerivedT>::LoadFromFile(const std::string &filename)
{
    HANDLE fileHandle = CreateFile(lpta_d3d_utils::ToWChar(filename).c_str(), GENERIC_READ, 
        false, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (INVALID_HANDLE_VALUE == fileHandle) {
        throw ShaderCompileFail();
    }
    
    HANDLE fileMemMap = CreateFileMapping(fileHandle, 0, PAGE_READONLY, 0, 0, 0);
    void *fileMapView = MapViewOfFile(fileMemMap, FILE_MAP_READ, 0, 0, 0);
    LPDIRECT3DVERTEXSHADER9 shader = Load(fileMapView);
    
    UnmapViewOfFile(fileMapView);   
    CloseHandle(fileMemMap);
    CloseHandle(fileHandle);

    return shader;
}

template <class ResourceT, class DxT, class DerivedT>
DxT LptaD3DShaderManager<ResourceT, DxT, DerivedT>::LoadAndCompile(const std::string &shader)
{
    LPD3DXBUFFER compiled;
    LPD3DXBUFFER errorMsg;
    HRESULT assembleResult = D3DXAssembleShader(
        shader.c_str(), shader.length() , NULL, NULL, 0, &compiled, &errorMsg); 

    if (SUCCEEDED(assembleResult)) {
        return Load(compiled->GetBufferPointer());
    }
    else {
        throw ShaderCompileFail();
    }
}

template <class ResourceT, class DxT, class DerivedT>
DxT LptaD3DShaderManager<ResourceT, DxT, DerivedT>::LoadAndCompileFromFile(const std::string &filename)
{
    LPD3DXBUFFER compiled;
    LPD3DXBUFFER errorMsg;
    HRESULT assembleResult = D3DXAssembleShaderFromFileW(
        lpta_d3d_utils::ToWChar(filename).c_str(), NULL, NULL, 0, &compiled, &errorMsg);
    
    if (SUCCEEDED(assembleResult)) {
        return Load(compiled->GetBufferPointer());
    }
    else {
        throw ShaderCompileFail();
    }
}

}

#endif