#ifndef _LPTAD3DSHADER_H_
#define _LPTAD3DSHADER_H_

#include <d3d9.h>
#include "LptaResource.h"

namespace lpta_d3d
{

class LptaD3DShader : public lpta::LptaResource
{
public:
    typedef LptaResource::ID D3D_SHADER_ID;

public:
    LptaD3DShader(D3D_SHADER_ID, LPDIRECT3DVERTEXSHADER9 shader);
    ~LptaD3DShader(void);

    LPDIRECT3DVERTEXSHADER9 GetShader(void) const;

private:
    LPDIRECT3DVERTEXSHADER9 shader;
};

}

#endif