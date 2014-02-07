#ifndef _LPTAD3DSKINMANAGER_H_
#define _LPTAD3DSKINMANAGER_H_

#include <d3d9.h>
#include "LptaSkinManagerImpl.h"

class LptaD3DSkinManager : public LptaSkinManagerImpl
{
public:
    LptaD3DSkinManager(LPDIRECT3DDEVICE9 d3ddev);
    ~LptaD3DSkinManager(void);

    virtual HRESULT AddSkin(const Lpta::LPTA_MATERIAL &material, unsigned int *skinId);
    virtual HRESULT AddTexture(unsigned int skinId,
        const Lpta::LPTA_TEXTURE &texture, bool enableTransparency);
    virtual HRESULT AddTextureHeightmapAsBump(unsigned int skinId, const string &fileName);

    virtual Lpta::LPTA_SKIN GetSkin(unsigned int skinId) const;
    virtual Lpta::LPTA_MATERIAL GetMaterial(unsigned int materialId) const;
    virtual Lpta::LPTA_TEXTURE GetTexture(unsigned int textureId) const;
    
private:
    LPDIRECT3DDEVICE9 d3ddev;

    HRESULT CreateTexture(Lpta::LPTA_TEXTURE *texture, bool transparent);
    HRESULT SetAlphaKey(LPDIRECT3DTEXTURE9 *texture, UCHAR r, UCHAR g, UCHAR b, UCHAR a);
    HRESULT SetTransparency(LPDIRECT3DTEXTURE9 *texture, UCHAR alpha);
    DWORD MakeD3DColor(UCHAR r, UCHAR g, UCHAR b, UCHAR a);
};

#endif