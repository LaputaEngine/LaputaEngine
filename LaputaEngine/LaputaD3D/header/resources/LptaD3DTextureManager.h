#ifndef _LPTAD3DTEXTUREMANAGER_H_
#define _LPTAD3DTEXTUREMANAGER_H_

#include <d3d9.h>
#include "LptaD3DTexture.h"
#include "LptaTextureManager.h"

namespace lpta_d3d
{
    
class LptaD3DTextureManager : public lpta::LptaTextureManager
{
public:
    LptaD3DTextureManager(LPDIRECT3DDEVICE9 d3ddev);
    ~LptaD3DTextureManager(void);

protected:
    virtual lpta::LptaTexture::DATA GenerateDefaultData(void);

private:
    LPDIRECT3DDEVICE9 d3ddev;
};

}

#endif