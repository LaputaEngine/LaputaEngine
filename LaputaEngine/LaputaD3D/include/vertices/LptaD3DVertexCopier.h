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
    typedef enum COPY_RESULT_TYPE
    {
        SUCCESS,
        FAILURE
    } COPY_RESULT;
    
public:
    LptaD3DVertexCopier(lpta::LptaVertexCollection *collection);
    virtual ~LptaD3DVertexCopier(void);

    unsigned int GetStride(void) const;
    unsigned int GetNumVertices(void) const;
    unsigned int ByteSize(void) const;

    COPY_RESULT CopyToBuffer(void *buffer, unsigned int bufferSize);

protected:
    virtual void Visit(lpta::LptaVertexCollection *collection);
    virtual void Visit(lpta::LptaUUVertexCollection *collection);
    virtual void Visit(lpta::LptaULVertexCollection *collection);

    template <class T>
    bool HasValidCopyBuffer(void) const;

private:
    lpta::LptaVertexCollection *collection;
    unsigned int stride;

    void *copyBuffer;
    unsigned int copyBufferSize;
};

}

#endif