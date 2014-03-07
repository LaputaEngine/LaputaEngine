#include "LptaNormalVector.h"
#include "vertices/LptaUUVertices.h"
#include "vertices/LptaD3DStaticBufferManager.h"

namespace lpta_d3d
{

LptaD3DStaticBufferManager::LptaD3DStaticBufferManager(LPDIRECT3DDEVICE9 d3ddev)
{
    // d3d expects at least one vertex and index
    lpta::UU_VERTEX vertex = {
        lpta_3d::POINT(0.0f, 0.0f, 0.0f),
        lpta_3d::LptaNormalVector::MakeFrom(1.0f, 0.0f, 0.0f),
        0.0f, 0.0f
    };
    lpta::LptaUUVertices vertices;
    vertices.AddVertex(vertex);
    lpta::INDICES indices;
    indices.push_back(0);
    LptaD3DStaticBufferResource defaultBuffer(GetNextId(), new LptaD3DStaticBuffer(
        d3ddev, &vertices, indices)
    );
    this->SetNullResource(defaultBuffer);
}

LptaD3DStaticBufferManager::~LptaD3DStaticBufferManager(void)
{
}

LptaD3DStaticBufferResource::ID LptaD3DStaticBufferManager::AddBuffer(LptaD3DStaticBuffer *buffer)
{
    LptaD3DStaticBufferResource bufferResource(GetNextId(), buffer);
    this->AddResource(bufferResource);
    return bufferResource.GetId();
}

}