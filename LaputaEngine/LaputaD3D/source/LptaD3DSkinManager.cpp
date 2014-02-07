#include <Windows.h>
#include <d3d9.h>
#include "LptaD3DSkinManager.h"
using std::shared_ptr;

typedef vector<Lpta::LPTA_TEXTURE> TEXTURES;

LptaD3DSkinManager::LptaD3DSkinManager(LPDIRECT3DDEVICE9 d3ddev) : d3ddev(d3ddev)
{
}

LptaD3DSkinManager::~LptaD3DSkinManager(void)
{
    TEXTURES liveTextures = textures;
    textures.clear();
    materials.clear();
    skins.clear();
    TEXTURES::iterator texture;
    for (texture = liveTextures.begin(); texture != liveTextures.end(); ++texture) {
        ((LPDIRECT3DTEXTURE9)texture->data.get())->Release();
    }
    liveTextures.clear();
}

HRESULT LptaD3DSkinManager::AddSkin(const Lpta::LPTA_MATERIAL &material, unsigned int *skinId)
{
    //todo
    return S_OK;
}

HRESULT LptaD3DSkinManager::AddTexture(unsigned int skinId,
    const Lpta::LPTA_TEXTURE &texture, bool enableTransparency)
{
    // todo
    return S_OK;
}

HRESULT LptaD3DSkinManager::AddTextureHeightmapAsBump(unsigned int skinId, const string &fileName)
{
    //todo
    return S_OK;
}

Lpta::LPTA_SKIN LptaD3DSkinManager::GetSkin(unsigned int skinId) const
{
    return ValidSkinId(skinId) ? skins[skinId] : Lpta::LPTA_SKIN();
}

Lpta::LPTA_MATERIAL LptaD3DSkinManager::GetMaterial(unsigned int materialId) const
{
    return ValidMaterialId(materialId) ? materials[materialId] : Lpta::LPTA_MATERIAL();
}

Lpta::LPTA_TEXTURE LptaD3DSkinManager::GetTexture(unsigned int textureId) const
{
    return ValidTextureId(textureId) ? textures[textureId] : Lpta::LPTA_TEXTURE();
}

HRESULT LptaD3DSkinManager::CreateTexture(Lpta::LPTA_TEXTURE *texture, bool transparent)
{
    //todo
    return S_OK;
}

HRESULT LptaD3DSkinManager::SetAlphaKey(LPDIRECT3DTEXTURE9 *texture, UCHAR r, UCHAR g, UCHAR b, UCHAR a)
{
    //todo
    return S_OK;
}

HRESULT LptaD3DSkinManager::SetTransparency(LPDIRECT3DTEXTURE9 *texture, UCHAR alpha)
{
    //todo
    return S_OK;
}

DWORD LptaD3DSkinManager::MakeD3DColor(UCHAR r, UCHAR g, UCHAR b, UCHAR a)
{
    //todo
    return S_OK;
}