#include <d3d9.h>
#include "LptaTexture.h"
#include "resources/LptaD3DTexture.h"
#include "resources/errors/TextureD3DFailure.h"
#include "resources/LptaD3DTextureManager.h"

namespace lpta_d3d
{

LptaD3DTextureManager::LptaD3DTextureManager(LPDIRECT3DDEVICE9 d3ddev) : d3ddev(d3ddev)
{
    SetNullResource(CreateNullResource());
}

LptaD3DTextureManager::~LptaD3DTextureManager(void)
{
}

LptaD3DTexture::TEXTURE_ID LptaD3DTextureManager::AddorRetrieveTexture(const std::string &filename, 
    bool transparent, float alpha,
    const LptaD3DTexture::COLOR_KEYS &colorKeys)
{
    for (RESOURCES::const_iterator it = resources.begin(); it != resources.end(); ++it) {
        const lpta::LptaTexture &texture = it->second;
        if (texture.GetFilename() == filename) {
            return texture.GetId();
        }
    }
    LptaD3DTexture d3dTexture(d3ddev, GetNextId(), filename, alpha, colorKeys);
    AddResource(d3dTexture);
    return d3dTexture.GetId();
}

lpta::LptaTexture::DATA LptaD3DTextureManager::GenerateDefaultData(void)
{
    LPDIRECT3DTEXTURE9 textureData = NULL;
    D3DLOCKED_RECT d3dLockedRect;
    HRESULT result = d3ddev->CreateTexture(
        DEFAULT_TEXTURE_WIDTH, DEFAULT_TEXTURE_HEIGHT,
        1, 0,
        D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
        &textureData,
        NULL
    );
    if (FAILED(result)) {
        throw TextureD3DFailure("could not obtain texture object for default");
    }
    result = textureData->LockRect(0, &d3dLockedRect, NULL, 0);
    if (FAILED(result)) {
        textureData->Release();
        throw TextureD3DFailure("failed to lock rectangle to set default texture color");
    }
    unsigned long *rawData = (unsigned long *)d3dLockedRect.pBits;
    for (unsigned long *pixel = rawData; 
        pixel < rawData + (DEFAULT_TEXTURE_WIDTH * DEFAULT_TEXTURE_HEIGHT); ++pixel) {

        *pixel = DEFAULT_TEXTURE_COLOR;
    }
    textureData->UnlockRect(0);
    return (lpta::LptaTexture::DATA)textureData;
}

}