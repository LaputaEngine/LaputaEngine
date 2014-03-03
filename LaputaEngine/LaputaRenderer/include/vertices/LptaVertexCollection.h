#ifndef _LPTAVERTEXCOLLECTION_H_
#define _LPTAVERTEXCOLLECTION_H_

#include "LptaVertexCollectionVisitor.h"

namespace lpta
{

// vertex type registry
typedef enum VERTEX_TYPE_TYPE
{
    VT_UNKNOWN,
    VT_UU,          // untransformed, unlit
    VT_UL,          // untransformed, lit
} VERTEX_TYPE;

class LptaVertexCollection
{
public:
    virtual ~LptaVertexCollection(void);

    VERTEX_TYPE GetType(void) const;

    virtual unsigned int GetNumVertices(void) const = 0;
    virtual void Accept(LptaVertexCollectionVisitor *visitor) = 0;

protected:
    LptaVertexCollection(VERTEX_TYPE vType);

private:
    const VERTEX_TYPE vertexType;
};

}

#endif