#include "resources/LptaD3DPixelShader.h"

namespace lpta_d3d
{

LptaD3DPixelShader::LptaD3DPixelShader(PIXEL_SHADER_ID id, LPDIRECT3DPIXELSHADER9 shader) :
    LptaResource(id), pixelShader(shader)
{
}

LptaD3DPixelShader::LptaD3DPixelShader(const LptaD3DPixelShader &copyTarget) :
    LptaD3DPixelShader(copyTarget.id, copyTarget.pixelShader)
{
    pixelShader->AddRef();
}

LptaD3DPixelShader::~LptaD3DPixelShader(void)
{
    pixelShader->Release();
}

LPDIRECT3DPIXELSHADER9 LptaD3DPixelShader::GetPixelShader(void) const
{
    return pixelShader;
}

}