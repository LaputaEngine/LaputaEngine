#ifndef _LPTANULLMESH_H_
#define _LPTANULLMESH_H_

#include "vertices/LptaULVertices.h"

namespace lpta
{

class LptaNullMesh : public LptaMesh
{
public:
    LptaNullMesh(void) {}
    ~LptaNullMesh(void) {}

    const LptaVertices &GetVertices(void) const { return vertices; }
    const INDICES &GetIndices(void) const { return indices; }

    unsigned int NumVertices(void) const { return 0; }
    unsigned int NumFaces(void) const { return 0; }

private:
    LptaULVertices vertices;
    INDICES indices;
};

}

#endif