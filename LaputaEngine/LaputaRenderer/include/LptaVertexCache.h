#ifndef _LPTAVERTEXCACHE_H_
#define _LPTAVERTEXCACHE_H_

#include <Windows.h>
#include "vertices/LptaVertices.h"
#include "vertices/LptaIndices.h"
#include "LptaResource.h"
#include "LptaSkin.h"

namespace lpta
{

class LptaVertexCache
{
public:
    virtual ~LptaVertexCache(void) {}

    virtual LptaResource::ID CreateStaticBuffer(LptaVertices *vertices, 
        const INDICES &indices) = 0;
    virtual HRESULT FlushStaticBuffer(LptaResource::ID bufferId) = 0;

    virtual HRESULT Render(LptaVertices *vertices, const INDICES &indices, 
        LptaSkin::SKIN_ID skinId) = 0;

    virtual HRESULT ForcedFlushAll(void) = 0;
    virtual HRESULT ForcedFlush(VERTEX_TYPE vertexType) = 0;
};

}

#endif