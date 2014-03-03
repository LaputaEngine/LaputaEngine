#include <stdexcept>
#include "vertices/LptaD3DVertex.h"
#include "vertices/errors/D3DBufferAllocationFailure.h"
#include "vertices/LptaD3DVertexCopier.h"
#include "vertices/LptaD3DDynamicBuffer.h"

#define USAGE (D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY)

namespace lpta_d3d
{

LptaD3DDynamicBuffer::LptaD3DDynamicBuffer(
    LPDIRECT3DDEVICE9 d3ddev, 
    lpta::VERTEX_TYPE vertexType,
    unsigned int maxVertices, unsigned int maxIndices) : 
        vertexBuffer(NULL), indexBuffer(NULL), vertexType(vertexType),
        maxVertices(maxVertices), maxIndices(maxIndices), numVertices(0), numIndices(0)
{
    try {
        {
            HRESULT result = d3ddev->CreateVertexBuffer(ToStride(vertexType) * maxVertices, 
                USAGE, 0, D3DPOOL_DEFAULT, &vertexBuffer, NULL);
            if (FAILED(result)) {
                throw std::runtime_error("failed to create vertex buffer");
            }
        }
        {
            HRESULT result = d3ddev->CreateIndexBuffer(sizeof(DWORD) * maxIndices,
                USAGE, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer, NULL);
            if (FAILED(result)) {
                throw std::runtime_error("failed to create index buffer");
            }
        }
    }
    catch (std::runtime_error) {
        if (NULL != vertexBuffer) {
            vertexBuffer->Release();
        }
        if (NULL != indexBuffer) {
            indexBuffer->Release();
        }
        throw D3DBufferAllocationFailure();
    }
}

LptaD3DDynamicBuffer::~LptaD3DDynamicBuffer(void)
{
    vertexBuffer->Release();
    indexBuffer->Release();
}

lpta::VERTEX_TYPE LptaD3DDynamicBuffer::GetVertexType(void) const
{
    return vertexType;   
}

bool LptaD3DDynamicBuffer::CanFit(const lpta::LptaVertexCollection &collection) const
{
    if (collection.GetType() != vertexType) {
        return false;
    }

    return (numVertices + collection.GetNumVertices()) <= maxVertices;
}

bool LptaD3DDynamicBuffer::AddVertices(lpta::LptaVertexCollection *collection)
{
    if (!CanFit(*collection)) {
        return false;
    }

    void *buffer;
    unsigned int byteSize = ToStride(collection->GetType()) * collection->GetNumVertices();
    DWORD lockFlag = numVertices > 0? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD;
    LptaD3DVertexCopier copier(collection);

    HRESULT lockResult = vertexBuffer->Lock(numVertices, byteSize, &buffer, lockFlag);
    if (FAILED(lockResult)) {
        // log error
        return false;
    }
    copier.CopyToBuffer(buffer, byteSize);
    vertexBuffer->Unlock();
    return true;
}

}