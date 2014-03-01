#ifndef _LPTAD3DVERTEXCOPIER_H_
#define _LPTAD3DVERTEXCOPIER_H_

#include <vector>
#include "vertices/LptaVertexCollectionVisitor.h"
#include "LptaD3DVertexBuffer.h"

namespace lpta_d3d
{

class LptaD3DVertexCopier : protected lpta::LptaVertexCollectionVisitor
{
public:
    LptaD3DVertexCopier(lpta::LptaVertexCollection *collection);
    virtual ~LptaD3DVertexCopier(void);

    unsigned int GetStride(void) const;
    unsigned int GetNumVertices(void) const;
    unsigned int ByteSize(void) const;

    void CopyToBuffer(void *buffer);

protected:
    virtual void Visit(lpta::LptaVertexCollection *collection);
    virtual void Visit(lpta::LptaUUVertexCollection *collection);
    virtual void Visit(lpta::LptaULVertexCollection *collection);

private:
    lpta::LptaVertexCollection *collection;
    unsigned int stride;

    void *copyBuffer;
};

}

#endif