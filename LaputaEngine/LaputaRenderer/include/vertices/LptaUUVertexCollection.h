#ifndef _LPTAUUVERTEXCOLLECTION_H_
#define _LPTAUUVERTEXCOLLECTION_H_

#include <vector>
#include "LptaVector.h"
#include "LptaVertexCollection.h"

namespace lpta
{

typedef struct UU_VERTEX_TYPE
{
    lpta_3d::POINT coordinate;
    lpta_3d::LptaVector normal;
    
    float tu;
    float tv;
} UU_VERTEX;

class LptaUUVertexCollection : public LptaVertexCollection
{
public:
    LptaUUVertexCollection(void);
    virtual ~LptaUUVertexCollection(void);

    virtual unsigned int GetNumVertices(void) const;
    virtual void Accept(LptaVertexCollectionVisitor *visitor);

    void AddVertex(const UU_VERTEX &vertex);
    const std::vector<UU_VERTEX> &GetVertices(void) const;
    
private:
    std::vector<UU_VERTEX> vertices;
};

}

#endif