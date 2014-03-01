#ifndef _LPTAD3DSHADER_H_
#define _LPTAD3DSHADER_H_

#include <d3d9.h>
#include "LptaResource.h"

namespace lpta_d3d
{

class LptaD3DVertexShader : public lpta::LptaResource
{
public:
    typedef LptaResource::ID VERTEX_SHADER_ID;

public:
    LptaD3DVertexShader(VERTEX_SHADER_ID, LPDIRECT3DVERTEXSHADER9 shader);
    LptaD3DVertexShader(const LptaD3DVertexShader &copyTarget);
    ~LptaD3DVertexShader(void);

    LPDIRECT3DVERTEXSHADER9 GetVertexShader(void) const;

private:
    LPDIRECT3DVERTEXSHADER9 vertexShader;
};

}

#endif