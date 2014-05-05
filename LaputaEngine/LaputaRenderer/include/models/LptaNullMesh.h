#ifndef _LPTANULLMESH_H_
#define _LPTANULLMESH_H_

namespace lpta
{

class LptaNullMesh : public LptaMesh
{
public:
    LptaNullMesh(void) {}
    ~LptaNullMesh(void) {}

    unsigned int NumVertices(void) const { return 0; }
    unsigned int NumFaces(void) const { return 0; }
};

}

#endif