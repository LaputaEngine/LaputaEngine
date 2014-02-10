#ifndef _LPTAD3DTEXTURE_H_
#define _LPTAD3DTEXTURE_H_

#include <string>
#include <d3d9.h>
#include "LptaTexture.h"
using std::string;

namespace lpta_d3d
{

class LptaD3DTexture : public lpta::LptaTexture<LPDIRECT3DTEXTURE9>
{
public:
    LptaD3DTexture(LPDIRECT3DDEVICE9 d3ddev, ID id, const string &filename, 
        float alpha, const COLOR_KEYS &colorKeys);
    LptaD3DTexture(ID id, const string &name, LPDIRECT3DTEXTURE9 data, 
        float alpha, const COLOR_KEYS &colorKeys);
    ~LptaD3DTexture(void);

private:
    static LPDIRECT3DTEXTURE9 D3DLoadTextureFile(LPDIRECT3DDEVICE9 d3ddev, const string &filename, bool alpha);
};

}

#endif