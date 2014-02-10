#ifndef _LPTAD3DTEXTUREMANAGER_H_
#define _LPTAD3DTEXTUREMANAGER_H_

#include <d3d9.h>
#include "LptaD3DTexture.h"
#include "LptaTextureManager.h"

namespace lpta_d3d
{
    
class LptaD3DTextureManager : 
    public lpta::LptaTextureManager<LptaD3DTexture, LptaD3DTextureManager>
{
public:
    LptaD3DTextureManager(LPDIRECT3DDEVICE9 d3ddev);
    ~LptaD3DTextureManager(void);

    static LptaD3DTexture CreateNullResource(LptaD3DTexture::TEXTURE_ID, 
        LptaD3DTextureManager *const manager);
protected:
    LPDIRECT3DTEXTURE9 GenerateDefaultData(void);

private:
    LPDIRECT3DDEVICE9 d3ddev;
};

}

#endif