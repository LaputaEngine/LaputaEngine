#ifndef _LPTAMESH_H_
#define _LPTAMESH_H_

#include <string>
#include "LptaResource.h"
#include "vertices/LptaVertices.h"
#include "vertices/LptaIndices.h"

namespace lpta
{

class LptaMeshLoadFailure
{
public:
    LptaMeshLoadFailure(const std::string &reason) : reason(reason) {}
    ~LptaMeshLoadFailure(void) {}

    const std::string reason;
};

class LptaMesh
{
public:
    LptaMesh(void) {}
    virtual ~LptaMesh(void) {}

    virtual const LptaVertices &GetVertices(void) const = 0;
    virtual const INDICES &GetIndices(void) const = 0;

    virtual unsigned int NumVertices(void) const = 0;
    virtual unsigned int NumFaces(void) const = 0;

    bool IsCached(void) const { return isCached; }
    void SetCached(LptaResource::ID cacheId);
    LptaResource::ID GetCacheId(void) const { return cacheId; }

private:
    bool isCached = false;
    LptaResource::ID cacheId;

public:
    static LptaMesh *LoadFromFile(const std::string &filename, 
        VERTEX_TYPE vertexType=VERTEX_TYPE::VT_UL);
};

}

#endif