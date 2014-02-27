#ifndef _LPTAVERTEXCOLLECTION_H_
#define _LPTAVERTEXCOLLECTION_H_

namespace lpta
{

// vertex type registry
typedef enum VERTEX_TYPE_TYPE
{
    VT_UU,          // untransformed, unlit
    VT_UL,          // untransformed, lit
} VERTEX_TYPE;

class LptaVertexCollection
{
public:
    virtual ~LptaVertexCollection(void);

    VERTEX_TYPE GetType(void) const;

protected:
    LptaVertexCollection(VERTEX_TYPE vType);

private:
    const VERTEX_TYPE vertexType;
};

}

#endif