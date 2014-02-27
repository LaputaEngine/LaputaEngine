#ifndef _LPTAD3DSHADERMANAGER_H_
#define _LPTAD3DSHADERMANAGER_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "LptaResource.h"
#include "LptaResourceManager.h"
#include "errors/ShaderCompileFail.h"

namespace lpta_d3d
{

template <class ResourceT, class DxT>
class LptaD3DShaderManager : public lpta::LptaResourceManager<ResourceT>
{
public:
    lpta::LptaResource::ID CompileAddShader(const std::string &program);

protected:
    virtual HRESULT D3DCreateShader(DWORD *shader, DxT *handle) = 0;

    DxT Load(void *program);
    DxT LoadAndCompile(const std::string &program);
};

///////////////////////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////
template <class ResourceT, class DxT>
lpta::LptaResource::ID LptaD3DShaderManager<ResourceT, DxT>::CompileAddShader(
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

///////////////////////////////////////////////////////////////////////////////
// protected
///////////////////////////////////////////////////////////
template <class ResourceT, class DxT>
DxT LptaD3DShaderManager<ResourceT, DxT>::Load(void *program)
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

template <class ResourceT, class DxT>
DxT LptaD3DShaderManager<ResourceT, DxT>::LoadAndCompile(const std::string &shader)
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

}

#endif