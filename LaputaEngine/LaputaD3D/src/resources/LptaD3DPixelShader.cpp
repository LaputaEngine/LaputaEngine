#include "resources/LptaD3DPixelShader.h"

namespace lpta_d3d
{

LptaD3DPixelShader::LptaD3DPixelShader(PIXEL_SHADER_ID id, LPDIRECT3DPIXELSHADER9 shader) :
    LptaResource(id), pixelShader(shader)
{
}

LptaD3DPixelShader::~LptaD3DPixelShader(void)
{
}

LPDIRECT3DPIXELSHADER9 LptaD3DPixelShader::GetPixelShader(void) const
{
    return pixelShader;
}

}