#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "LptaVector.h"
#include "models/LptaAssimpMesh.h"
#include "vertices/LptaULVertices.h"
#include "vertices/LptaUUVertices.h"

#define SUCCESSFUL
#define IMPORT_FLAGS aiProcessPreset_TargetRealtime_Fast

namespace lpta
{

Assimp::Importer LptaAssimpMesh::assetImporter;


// LptaAssimpMesh(filename)
inline bool IsValidScene(const aiScene &scene);
inline LptaVertices *CopyMesh(VERTEX_TYPE vertexType, INDICES &indices, 
    aiMesh *mesh);
inline LptaULVertices *CopyULMesh(INDICES &indices, aiMesh *mesh);
inline LptaUUVertices *CopyUUMesh(INDICES &indices, aiMesh *mesh);


LptaAssimpMesh::LptaAssimpMesh(VERTEX_TYPE vertexType, const std::string &filename)
{
    if (SUCCESSFUL assetImporter.ReadFile(filename, IMPORT_FLAGS)) {
        const aiScene *scene = assetImporter.GetOrphanedScene();
        try {
            if (!scene || !IsValidScene(*scene)) {
                throw LptaMeshLoadFailure("Not a valid mesh file");
            }
            vertices = CopyMesh(vertexType, indices, scene->mMeshes[0]);
        }
        catch (const LptaMeshLoadFailure &loadFailure) {
            if (scene) {
                aiReleaseImport(scene);
            }
            throw loadFailure;
        }
        aiReleaseImport(scene);     
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
LptaVertices *CopyMesh(VERTEX_TYPE vertexType, INDICES &indices, aiMesh *mesh)
{
    switch (vertexType) {
    case VERTEX_TYPE::VT_UL:
        return CopyULMesh(indices, mesh);
    case VERTEX_TYPE::VT_UU:
        return CopyUUMesh(indices, mesh);
    default:
        throw LptaMeshLoadFailure("Don't know how to copy vertices for mesh");
    };
}
// todo eliminate code dup
// todo account for cases where face doesn't use 3 indices, might be post
// processing flags
LptaULVertices *CopyULMesh(INDICES &indices, aiMesh *mesh)
{
    LptaULVertices *vertices = new LptaULVertices();
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        UL_VERTEX vertex;
        auto meshVertex = mesh->mVertices[i];
        // todo use actual values
        vertex.coordinate = lpta_3d::LptaVector(meshVertex.x,
            meshVertex.y, meshVertex.z);
        vertex.tu = 0.0f;
        vertex.tv = 0.0f;
        vertices->AddVertex(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        auto face = mesh->mFaces[i];
        for (unsigned int vIndex = 0; vIndex < face.mNumIndices; ++vIndex) {
            indices.push_back(face.mIndices[vIndex]);
        }
    }
    return vertices;   
}
LptaUUVertices *CopyUUMesh(INDICES &indices, aiMesh *mesh)
{
    LptaUUVertices *vertices = new LptaUUVertices();
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        UU_VERTEX vertex;
        auto meshVertex = mesh->mVertices[i];
        // todo use actual values
        vertex.coordinate = lpta_3d::LptaVector(meshVertex.x,
            meshVertex.y, meshVertex.z);
        vertex.tu = 0.0f;
        vertex.tv = 0.0f;
        vertices->AddVertex(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        auto face = mesh->mFaces[i];
        for (unsigned int vIndex = 0; vIndex < face.mNumIndices; ++vIndex) {
            indices.push_back(face.mIndices[vIndex]);
        }
    }
    return vertices;
}

LptaAssimpMesh::~LptaAssimpMesh(void)
{
    delete vertices;
}


const LptaVertices &LptaAssimpMesh::GetVertices(void) const
{
    return *vertices;
}

const INDICES &LptaAssimpMesh::GetIndices(void) const
{
    return indices;
}


unsigned int LptaAssimpMesh::NumVertices(void) const
{
    return vertices->GetNumVertices();
}

// todo fix case for where faces aren't triangles (if needed)
unsigned int LptaAssimpMesh::NumFaces(void) const
{
    return indices.size();
}

}