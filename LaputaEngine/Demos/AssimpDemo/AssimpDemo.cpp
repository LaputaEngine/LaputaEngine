#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <memory>
#include <iostream>
using namespace std;

// #define VERBOSE_DUMP

// just a sloppily written demo to figure out how to use the library

int main(int argc, char *argv[]) 
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("test.3ds", aiProcessPreset_TargetRealtime_Fast);
    cout << "**************** Assimp Demo ****************" << endl;
    cout << "Loading teapot.obj..." << endl;
    if (scene) {
        cout << "Scene successfully loaded!" << endl;
        cout << "Stats:" << endl
            << "[Meshes] >> " << scene->mNumMeshes << endl;
        cout << "Attempting to access teapot..." << endl;
        /*if (scene->mNumMeshes != 1) {
            cout << "Unexpected number of meshes in scene..." << endl;
            return false;
        }*/
        const aiMesh *teapot = scene->mMeshes[0];
        if (!teapot) {
            cout << "Unexpected value for teapot pointer..." << endl;
            return false;
        }
        cout << "Teapot successfully accessed!" << endl;
        cout << "Stats:" << endl
            << "[Name] >> " << teapot->mName.C_Str() << endl
            << "[Vertices] >> " << teapot->mNumVertices << endl
            << "[Faces] >> " << teapot->mNumFaces << endl;
#ifdef VERBOSE_DUMP
        cout << "[Vertices] >> " << endl;
        for (unsigned int i = 0; i < teapot->mNumVertices; ++i) {
            cout << teapot->mVertices[i].x << ", " << teapot->mVertices[i].y << ", " << teapot->mVertices[i].z << endl;
        }
        cout << "[Faces] >> " << endl;
        for (unsigned int i = 0; i < teapot->mNumFaces; ++i) {
            for (unsigned int j = 0; j < teapot->mFaces[i].mNumIndices; ++j) {
                cout << teapot->mFaces[i].mIndices[j];
                if (j != teapot->mFaces[i].mNumIndices - 1) {
                    cout << ", ";
                }
                else {
                    cout << endl;
                }
            }
        }
#endif
        return true;
    }
    else {
        cout << " >>> !!! >>> " << importer.GetErrorString() << endl;
        cout << "Model load failed..." << endl;
        return false;
    }
}