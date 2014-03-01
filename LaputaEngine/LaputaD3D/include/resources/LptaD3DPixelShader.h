#ifndef _LPTAD3DPIXELSHADER_H_
#define _LPTAD3DPIXELSHADER_H_

#include <d3d9.h>
#include "LptaResource.h"
#include "LptaD3DShaderManager.h"

namespace lpta_d3d
{

class LptaD3DPixelShader : public lpta::LptaResource
{
public:
    typedef lpta::LptaResource::ID PIXEL_SHADER_ID;

public:
    LptaD3DPixelShader(PIXEL_SHADER_ID id, LPDIRECT3DPIXELSHADER9 shader);
    LptaD3DPixelShader(const LptaD3DPixelShader &copyTarget);
    ~LptaD3DPixelShader(void);

    LPDIRECT3DPIXELSHADER9 GetPixelShader(void) const;

private:
    LPDIRECT3DPIXELSHADER9 pixelShader;
};

}

#endif