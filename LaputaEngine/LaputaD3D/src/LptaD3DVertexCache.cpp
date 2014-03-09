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

///////////////////////////////////////////////////////////////////////////////
// Static buffers
/////////////////////////////////////////////////////////////////////
LptaD3DStaticBufferResource::ID LptaD3DVertexCache::CreateStaticBuffer(
    lpta::LptaVertices *vertices, const lpta::INDICES &indices, lpta::LptaSkin::SKIN_ID skinId)
{
    lpta::LptaResource::ID id = staticBuffers.AddBuffer(
        new LptaD3DStaticBuffer(d3ddev, vertices, indices, skinId)
    );
    return id;
}

HRESULT LptaD3DVertexCache::FlushStaticBuffer(LptaD3DStaticBufferResource::ID buffer)
{
    // todo implement
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Dynamic buffers
/////////////////////////////////////////////////////////////////////
HRESULT LptaD3DVertexCache::Render(lpta::LptaVertices *vertices, const lpta::INDICES &indices, 
    lpta::LptaSkin::SKIN_ID skinId)
{
    // todo implement
    return E_FAIL;
}

HRESULT LptaD3DVertexCache::ForcedFlushAll(void)
{
    // todo implement
    return E_FAIL;
}

HRESULT LptaD3DVertexCache::ForcedFlush(lpta::VERTEX_TYPE vertexType)
{
    // todo implement
    return E_FAIL;
}

}