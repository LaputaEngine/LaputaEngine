#include "LptaD3DVertexCache.h"

namespace lpta_d3d
{

LptaD3DVertexCache::LptaD3DVertexCache(LPDIRECT3DDEVICE9 d3ddev) : 
    d3ddev(d3ddev), staticBuffers(LptaD3DStaticBufferManager(d3ddev))
{
}

LptaD3DVertexCache::~LptaD3DVertexCache(void)
{
}

LptaD3DStaticBufferResource::ID LptaD3DVertexCache::CreateStaticBuffer(
    lpta::LptaVertices *vertices, const lpta::INDICES &indices)
{
    lpta::LptaResource::ID id = staticBuffers.AddBuffer(
        new LptaD3DStaticBuffer(d3ddev, vertices, indices)
    );
    return id;
}

HRESULT LptaD3DVertexCache::FlushStaticBuffer(LptaD3DStaticBufferResource::ID buffer)
{
    return S_OK;
}

void LptaD3DVertexCache::FlushAll(void)
{
}

}