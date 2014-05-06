#include "models/LptaMesh.h"
#include "models/LptaNullMesh.h"
#include "models/LptaAssimpMesh.h"

namespace lpta
{

#pragma warning( push )
#pragma warning( disable : 4101 )
LptaMesh *LptaMesh::LoadFromFile(const std::string &filename, 
    VERTEX_TYPE vertexType)
{
    try {
        return new LptaAssimpMesh(vertexType, filename);
    }
    catch (const LptaMeshLoadFailure &failure) {
        // log error
        return new LptaNullMesh();
    }
}
#pragma warning( pop )

void LptaMesh::SetCached(LptaResource::ID cacheId)
{
    this->cacheId = cacheId;
    this->isCached = true;
}

}