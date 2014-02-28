#ifndef _LPTAD3DVERTEXCOLLECTIONVISITOR_H_
#define _LPTAD3DVERTEXCOLLECTIONVISITOR_H_

#include <vector>
#include "vertices/LptaVertexCollectionVisitor.h"
#include "LptaD3DStaticBuffer.h"

namespace lpta_d3d
{

class LptaD3DVertexCollectionVisitor : public lpta::LptaVertexCollectionVisitor
{
public:
    LptaD3DVertexCollectionVisitor(void);
    virtual ~LptaD3DVertexCollectionVisitor(void);

    virtual void Visit(lpta::LptaVertexCollection *collection);
    virtual void Visit(lpta::LptaUUVertexCollection *collection);
    virtual void Visit(lpta::LptaULVertexCollection *collection);

    const std::vector<LptaD3DStaticBuffer> &GetTransforms(void) const;

private:
    std::vector<LptaD3DStaticBuffer> transforms;
};

}

#endif