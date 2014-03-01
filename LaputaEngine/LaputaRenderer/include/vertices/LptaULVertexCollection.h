#ifndef _LPTAULVERTEXCOLLECTION_H_
#define _LPTAULVERTEXCOLLECTION_H_

#include <vector>
#include "LptaVector.h"
#include "LptaColor.h"
#include "LptaVertexCollection.h"

namespace lpta
{

typedef struct UL_VERTEX_TYPE
{
    lpta_3d::POINT coordinate;
    LptaColor color;

    float tu;
    float tv;
} UL_VERTEX;

class LptaULVertexCollection : public LptaVertexCollection
{
public:
    LptaULVertexCollection(void);
    virtual ~LptaULVertexCollection(void);

    virtual unsigned int GetNumVertices(void) const;
    virtual void Accept(LptaVertexCollectionVisitor *visitor);

    void AddVertex(const UL_VERTEX &vertex);
    const std::vector<UL_VERTEX> &GetVertices(void) const;

private:
    std::vector<UL_VERTEX> vertices;
};

}

#endif