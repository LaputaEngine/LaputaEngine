#ifndef _LPTAD3DVERTEXCACHE_H_
#define _LPTAD3DVERTEXCACHE_H_

#include <memory>
#include <vector>
#include <d3d9.h>
#include "vertices/LptaD3DStaticBufferManager.h"
#include "vertices/LptaD3DDynamicBuffer.h"

namespace lpta_d3d
{

class LptaD3DVertexCache
{
public:
    typedef std::unique_ptr<LptaD3DDynamicBuffer> DYNAMIC_BUFFER;

public:
    LptaD3DVertexCache(LPDIRECT3DDEVICE9 d3ddev);
    ~LptaD3DVertexCache(void);

    void FlushAll(void);

private:
    LPDIRECT3DDEVICE9 d3ddev;
    
    LptaD3DStaticBufferManager staticBuffers;
    std::vector<DYNAMIC_BUFFER> dynamicBuffers;
};

}

#endif