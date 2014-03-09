#include <algorithm>
#include "vertices/errors/D3DBufferAllocationFailure.h"
#include "vertices/LptaD3DVertexCopier.h"
#include "vertices/LptaD3DVertex.h"
#include "vertices/LptaD3DStaticBuffer.h"

#define LOCK_ALL 0

namespace lpta_d3d
{

// todo possibly merge the codebase with dynamic buffer, think about creating
// an inheritance hierarchy
LptaD3DStaticBuffer::LptaD3DStaticBuffer(
    LPDIRECT3DDEVICE9 d3ddev,
    lpta::LptaVertices *vertices, 
    const lpta::INDICES &indices,
    const lpta::LptaSkin::SKIN_ID skinId,
    bool useShader) :
        vertexType(vertices->GetType()), vertexBuffer(nullptr), indexBuffer(nullptr),
        skinId(skinId), numVertices(vertices->GetNumVertices()), numIndices(indices.size())
{
    try {
        LptaD3DVertexCopier copier(vertices);
        if (SUCCEEDED(d3ddev->CreateVertexBuffer(
                copier.ByteSize(),
                D3DUSAGE_WRITEONLY, 
                useShader? 0 : ToFVF(vertexType), 
                D3DPOOL_DEFAULT, 
                &vertexBuffer, 
                nullptr)) &&
            SUCCEEDED(d3ddev->CreateIndexBuffer(
                indices.size() * sizeof(DWORD), 
                D3DUSAGE_WRITEONLY, 
                D3DFMT_INDEX16, 
                D3DPOOL_DEFAULT, 
                &indexBuffer, 
                nullptr))
        ) {
            {
                void *writeBuffer;
                if (SUCCEEDED(vertexBuffer->Lock(LOCK_ALL, LOCK_ALL, &writeBuffer, 0))) {
                    copier.CopyToBuffer(writeBuffer, copier.ByteSize());
                    vertexBuffer->Unlock();
                }
                else {
                    throw D3DBufferAllocationFailure();
                }
            }
            {
                DWORD *writeBuffer;
                if (SUCCEEDED(indexBuffer->Lock(LOCK_ALL, LOCK_ALL, 
                    reinterpret_cast<void **>(&writeBuffer), 0))
                ) {
                    for (unsigned int i = 0; i < indices.size(); ++i) {
                        writeBuffer[i] = static_cast<DWORD>(indices.at(i));
                    }
                    indexBuffer->Unlock();
                }
                else {
                    throw D3DBufferAllocationFailure();
                }
            }
        }
        else {
            throw D3DBufferAllocationFailure();
        }
    }
    catch (D3DBufferAllocationFailure e) {
        // todo throw more diverse exceptions for debug purposes
        // log error
        if (vertexBuffer) {
            vertexBuffer->Release();
        }
        if (indexBuffer) {
            indexBuffer->Release();
        }
        throw D3DBufferAllocationFailure();
    }
}

LptaD3DStaticBuffer::~LptaD3DStaticBuffer(void)
{
    vertexBuffer->Release();
    indexBuffer->Release();
}

}