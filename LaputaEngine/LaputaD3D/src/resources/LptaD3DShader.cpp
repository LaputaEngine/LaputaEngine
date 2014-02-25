#include "resources/LptaD3DShader.h"

namespace lpta_d3d
{

LptaD3DShader::LptaD3DShader(D3D_SHADER_ID id, LPDIRECT3DVERTEXSHADER9 shader) :
    LptaResource(id), shader(shader)
{
}

LptaD3DShader::~LptaD3DShader(void)
{
    // todo figure out why this call incurs an access violation
    //shader->Release();
}

LPDIRECT3DVERTEXSHADER9 LptaD3DShader::GetShader(void) const
{
    return shader;
}

}