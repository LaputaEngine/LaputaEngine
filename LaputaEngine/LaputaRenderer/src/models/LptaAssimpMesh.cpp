#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "models/LptaAssimpMesh.h"

#define SUCCESSFUL
#define IMPORT_FLAGS aiProcessPreset_TargetRealtime_Fast

namespace lpta
{

Assimp::Importer LptaAssimpMesh::assetImporter;


// LptaAssimpMesh(filename)
inline bool IsValidScene(const aiScene &scene);


LptaAssimpMesh::LptaAssimpMesh(const std::string &filename)
{
    auto foo = assetImporter.ReadFile(filename, IMPORT_FLAGS);
    //if (SUCCESSFUL assetImporter.ReadFile(filename, IMPORT_FLAGS)) {
    if (SUCCESSFUL foo) {
        scene = assetImporter.GetOrphanedScene();
        if (scene && IsValidScene(*scene)) {
            mesh = scene->mMeshes[0];
        }
        else {
            if (scene) {
                aiReleaseImport(scene);
            }
            throw LptaMeshLoadFailure("Not a valid mesh file");
        }
    }
    else {
        // log error
        throw LptaMeshLoadFailure(assetImporter.GetErrorString());
    }
}
bool IsValidScene(const aiScene &scene)
{
    return scene.mNumMeshes == 1;
}

LptaAssimpMesh::~LptaAssimpMesh(void)
{
    aiReleaseImport(scene);
}


unsigned int LptaAssimpMesh::NumVertices(void) const
{
    return mesh->mNumVertices;
}

unsigned int LptaAssimpMesh::NumFaces(void) const
{
    return mesh->mNumFaces;
}

}