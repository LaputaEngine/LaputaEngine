#ifndef _LPTAVERTICES_H_
#define _LPTAVERTICES_H_

#include "LptaVerticesVisitor.h"

namespace lpta
{

// vertex type registry
typedef enum VERTEX_TYPE_TYPE
{
    VT_UNKNOWN,
    VT_UU,          // untransformed, unlit
    VT_UL,          // untransformed, lit
} VERTEX_TYPE;

class LptaVertices
{
public:
    virtual ~LptaVertices(void);

    VERTEX_TYPE GetType(void) const;

    virtual unsigned int GetNumVertices(void) const = 0;
    virtual void Accept(LptaVerticesVisitor *visitor) const = 0;

protected:
    LptaVertices(VERTEX_TYPE vType);

private:
    const VERTEX_TYPE vertexType;
};

}

#endif