#include "resources/LptaD3DVertexShader.h"

namespace lpta_d3d
{

LptaD3DVertexShader::LptaD3DVertexShader(VERTEX_SHADER_ID id, LPDIRECT3DVERTEXSHADER9 shader) :
    LptaResource(id), vertexShader(shader)
{
}

LptaD3DVertexShader::LptaD3DVertexShader(const LptaD3DVertexShader &copyTarget) :
    LptaD3DVertexShader(copyTarget.id, copyTarget.vertexShader)
{
    vertexShader->AddRef();
}

LptaD3DVertexShader::~LptaD3DVertexShader(void)
{
    vertexShader->Release();
}

LPDIRECT3DVERTEXSHADER9 LptaD3DVertexShader::GetVertexShader(void) const
{
    return vertexShader;
}

}