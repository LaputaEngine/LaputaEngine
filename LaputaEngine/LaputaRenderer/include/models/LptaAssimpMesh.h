#ifndef _LPTAASSIMMESH_H_
#define _LPTAASSIMMESH_H_

#include <string>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "LptaMesh.h"

namespace lpta
{

class LptaAssimpMesh : public LptaMesh
{
public:
    LptaAssimpMesh(VERTEX_TYPE vertexType, const std::string &filename);
    ~LptaAssimpMesh(void);

    const LptaVertices &GetVertices(void) const;
    const INDICES &GetIndices(void) const;

    unsigned int NumVertices(void) const;
    unsigned int NumFaces(void) const;

private:
    LptaVertices *vertices = nullptr;
    INDICES indices;

private:
    static Assimp::Importer assetImporter;
};

}

#endif