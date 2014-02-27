#ifndef _LPTAVERTEXCACHEMANAGER_H_
#define _LPTAVERTEXCACHEMANAGER_H_

#include <vector>
#include <Windows.h>
#include "vertices/LptaVertexCollection.h"
#include "LptaSkin.h"
#include "LptaResource.h"

namespace lpta
{

class LptaVertexCacheManager
{
public:
    typedef LptaResource::ID VCACHE_ID;

public:
    virtual HRESULT CreateStaticBuffer(const LptaVertexCollection &collection, 
        unsigned int *bufferId) = 0;

    virtual HRESULT Render(const LptaVertexCollection &collection, LptaSkin::SKIN_ID skinId) = 0;
    virtual HRESULT Render(unsigned int bufferId);
    
    virtual HRESULT ForceFlushBuffers(void) = 0;
    virtual HRESULT ForceFlushBuffers(VERTEX_TYPE vertexType) = 0;
};

}

#endif