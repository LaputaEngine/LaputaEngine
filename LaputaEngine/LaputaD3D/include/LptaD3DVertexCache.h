#ifndef _LPTAD3DVERTEXCACHE_H_
#define _LPTAD3DVERTEXCACHE_H_

#include <vector>
#include <d3d9.h>
#include "vertices/LptaD3DDynamicBuffer.h"
#include "vertices/LptaD3DStaticBuffer.h"

namespace lpta_d3d
{

class LptaD3DVertexCache
{
public:
    

private:
    LPDIRECT3DDEVICE9 d3ddev;

    std::vector<LptaD3DStaticBuffer> staticBuffers;
    std::vector<LptaD3DDynamicBuffer> dynamicBuffers;
};

}

#endif