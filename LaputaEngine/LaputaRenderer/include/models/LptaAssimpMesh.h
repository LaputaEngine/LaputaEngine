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
    LptaAssimpMesh(const std::string &filename);
    ~LptaAssimpMesh(void);

    unsigned int NumVertices(void) const;
    unsigned int NumFaces(void) const;

private:
    const aiScene *scene;
    const aiMesh *mesh;

private:
    static Assimp::Importer assetImporter;
};

}

#endif