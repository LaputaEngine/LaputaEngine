#ifndef _LPTAD3DVERTEXCACHE_H_
#define _LPTAD3DVERTEXCACHE_H_

#include <memory>
#include <vector>
#include <d3d9.h>
#include "LptaSkinManager.h"
#include "LptaMaterialManager.h"
#include "LptaTextureManager.h"
#include "resources/LptaD3DTextureManager.h"
#include "LptaVertexCache.h"
#include "vertices/LptaD3DStaticBufferManager.h"
#include "vertices/LptaD3DDynamicBuffer.h"
using std::unique_ptr;

namespace lpta_d3d
{

class LptaD3DVertexCache : public lpta::LptaVertexCache
{
public:
    typedef std::unique_ptr<LptaD3DDynamicBuffer> DYNAMIC_BUFFER;

public:
    LptaD3DVertexCache(const LptaD3DVertexCache &copy) = delete;

    LptaD3DVertexCache(LPDIRECT3DDEVICE9 d3ddev);
    virtual ~LptaD3DVertexCache(void);

    ///////////////////////////////////////////////////////////////////////////
    // Manager accessors
    /////////////////////////////////////////////////////////////////
    lpta::LptaSkinManager *GetSkinManager(void) const { return skinManager.get(); }
    lpta::LptaMaterialManager *GetMaterialManager(void) const { return materialManager.get(); }
    lpta::LptaTextureManager *GetTextureManager(void) const { return textureManager.get(); }

    ///////////////////////////////////////////////////////////////////////////
    // Static Buffers
    /////////////////////////////////////////////////////////////////
    virtual LptaD3DStaticBufferResource::ID CreateStaticBuffer(lpta::LptaVertices *vertices, 
        const lpta::INDICES &indices, lpta::LptaSkin::SKIN_ID skinId);
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
    
    // vertex buffers
    LptaD3DStaticBufferManager staticBuffers;
    std::vector<DYNAMIC_BUFFER> dynamicBuffers;

    // managers
    // note: skin manager depends on material manager, declaration ordering is
    // important
    const unique_ptr<lpta::LptaMaterialManager> materialManager;
    const unique_ptr<lpta::LptaSkinManager> skinManager;
    const unique_ptr<LptaD3DTextureManager> textureManager;
};

}

#endif