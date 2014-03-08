#ifndef _LPTAD3DVERTEXCACHE_H_
#define _LPTAD3DVERTEXCACHE_H_

#include <memory>
#include <vector>
#include <d3d9.h>
#include "LptaVertexCache.h"
#include "vertices/LptaD3DStaticBufferManager.h"
#include "vertices/LptaD3DDynamicBuffer.h"

namespace lpta_d3d
{

class LptaD3DVertexCache : lpta::LptaVertexCache
{
public:
    typedef std::unique_ptr<LptaD3DDynamicBuffer> DYNAMIC_BUFFER;

public:
    LptaD3DVertexCache(const LptaD3DVertexCache &copy) = delete;

    LptaD3DVertexCache(LPDIRECT3DDEVICE9 d3ddev);
    virtual ~LptaD3DVertexCache(void);

    ///////////////////////////////////////////////////////////////////////////
    // Static Buffers
    /////////////////////////////////////////////////////////////////
    virtual LptaD3DStaticBufferResource::ID CreateStaticBuffer(lpta::LptaVertices *vertices, 
        const lpta::INDICES &indices);
    virtual HRESULT FlushStaticBuffer(LptaD3DStaticBufferResource::ID buffer);
    
    ///////////////////////////////////////////////////////////////////////////
    // Dynamic Buffers
    /////////////////////////////////////////////////////////////////
    virtual HRESULT Render(lpta::LptaVertices *vertices, const lpta::INDICES &indices, 
        lpta::LptaSkin::SKIN_ID skinId);
    virtual HRESULT ForcedFlushAll(void);
    virtual HRESULT ForcedFlush(lpta::VERTEX_TYPE vertexType);

private:
    LPDIRECT3DDEVICE9 d3ddev;
    
    LptaD3DStaticBufferManager staticBuffers;
    std::vector<DYNAMIC_BUFFER> dynamicBuffers;
};

}

#endif