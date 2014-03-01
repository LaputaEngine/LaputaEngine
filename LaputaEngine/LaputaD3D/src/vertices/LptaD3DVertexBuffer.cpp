#include "vertices/LptaD3DVertexBuffer.h"

namespace lpta_d3d
{

LptaD3DVertexBuffer::LptaD3DVertexBuffer(
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer,
    LPDIRECT3DINDEXBUFFER9 indexBuffer) : vertexBuffer(vertexBuffer), indexBuffer(indexBuffer)
{
}

LptaD3DVertexBuffer::LptaD3DVertexBuffer(const LptaD3DVertexBuffer &copyTarget) :
    LptaD3DVertexBuffer(copyTarget.vertexBuffer, copyTarget.indexBuffer)
{
    vertexBuffer->AddRef();
    indexBuffer->AddRef();
}

LptaD3DVertexBuffer::~LptaD3DVertexBuffer(void)
{
    vertexBuffer->Release();
    indexBuffer->Release();
}

}