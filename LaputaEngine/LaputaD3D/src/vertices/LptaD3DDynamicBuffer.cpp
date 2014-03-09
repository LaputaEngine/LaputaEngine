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
    unsigned int maxVertices, unsigned int maxIndices,
    lpta::LptaSkin::SKIN_ID skinId) : 
        vertexBuffer(nullptr), indexBuffer(nullptr), vertexType(vertexType),
        maxVertices(maxVertices), maxIndices(maxIndices), numVertices(0), numIndices(0),
        skinId(skinId)
{
    try {
        {
            HRESULT result = d3ddev->CreateVertexBuffer(ToStride(vertexType) * maxVertices, 
                USAGE, 0, D3DPOOL_DEFAULT, &vertexBuffer, nullptr);
            if (FAILED(result)) {
                throw std::runtime_error("failed to create vertex buffer");
            }
        }
        {
            HRESULT result = d3ddev->CreateIndexBuffer(sizeof(DWORD) * maxIndices,
                USAGE, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer, nullptr);
            if (FAILED(result)) {
                throw std::runtime_error("failed to create index buffer");
            }
        }
    }
    catch (std::runtime_error) {
        if (nullptr != vertexBuffer) {
            vertexBuffer->Release();
        }
        if (nullptr != indexBuffer) {
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

bool LptaD3DDynamicBuffer::CanFit(
    const lpta::LptaVertices &vertices, const lpta::INDICES &indices) const
{
    return CanFit(vertices) && (numIndices + indices.size()) <= maxIndices;
}
bool LptaD3DDynamicBuffer::CanFit(const lpta::LptaVertices &vertices) const
{
    if (vertices.GetType() != vertexType) {
        return false;
    }

    return (numVertices + vertices.GetNumVertices()) <= maxVertices;
}

bool LptaD3DDynamicBuffer::AddVertices(lpta::LptaVertices *vertices)
{
    lpta::INDICES empty;
    return Add(vertices, empty);
}
bool LptaD3DDynamicBuffer::Add(lpta::LptaVertices *vertices, const lpta::INDICES &indices)
{
    if (!CanFit(*vertices, indices)) {
        return false;
    }

    void *vertexWriteBuffer;
    unsigned int vertexByteSize = ToStride(vertices->GetType()) * vertices->GetNumVertices();

    DWORD *indexWriteBuffer;
    unsigned int indexByteSize = sizeof(DWORD) * indices.size();
    unsigned int indexOffset = numIndices;

    DWORD lockFlag = numVertices > 0? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD;

    if (!LockedBuffers(&vertexWriteBuffer, vertexByteSize, 
        &indexWriteBuffer, indexByteSize, lockFlag)) {

        // log error
        return false;
    }

    LptaD3DVertexCopier copier(vertices);

    copier.CopyToBuffer(vertexWriteBuffer, vertexByteSize);
    numVertices += vertices->GetNumVertices();

    for (unsigned int i = 0; i < indices.size(); ++i) {
        indexWriteBuffer[i] = static_cast<DWORD>(indices.at(i)) + indexOffset;
    }
    numIndices += indices.size();

    vertexBuffer->Unlock();
    indexBuffer->Unlock();
    return true;

}

bool LptaD3DDynamicBuffer::LockedBuffers(void **vertexWriteBuffer, unsigned int vertexByteSize, 
    DWORD **indexWriteBuffer, unsigned int indexByteSize, DWORD lockFlag)
{
    if (SUCCEEDED(vertexBuffer->Lock(numVertices, vertexByteSize, vertexWriteBuffer, lockFlag))) {
        if (SUCCEEDED(indexBuffer->Lock(numIndices, indexByteSize, 
            reinterpret_cast<void **>(indexWriteBuffer), lockFlag))) {

            return true;
        }
        else {
            vertexBuffer->Unlock();
            return false;
        }
    }
    return false;
}

}