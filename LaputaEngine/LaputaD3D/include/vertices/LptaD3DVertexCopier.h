#ifndef _LPTAD3DVERTEXCOPIER_H_
#define _LPTAD3DVERTEXCOPIER_H_

#include <vector>
#include "vertices/LptaVerticesVisitor.h"
#include "vertices/LptaVertices.h"
#include "LptaD3DVertexBuffer.h"

namespace lpta_d3d
{

class LptaD3DVertexCopier : protected lpta::LptaVerticesVisitor
{
public:
    typedef enum COPY_RESULT_TYPE
    {
        SUCCESS,
        FAILURE
    } COPY_RESULT;
    
public:
    LptaD3DVertexCopier(lpta::LptaVertices *collection);
    virtual ~LptaD3DVertexCopier(void);

    lpta::VERTEX_TYPE GetVertexType(void) const;
    unsigned int Stride(void) const;
    unsigned int NumVertices(void) const;
    unsigned int ByteSize(void) const;

    COPY_RESULT CopyToBuffer(void *buffer, unsigned int bufferSize);

protected:
    virtual void Visit(lpta::LptaVertices *collection);
    virtual void Visit(lpta::LptaUUVertices *collection);
    virtual void Visit(lpta::LptaULVertices *collection);

    template <class T>
    bool HasValidCopyBuffer(void) const;

private:
    lpta::LptaVertices *collection;

    void *copyBuffer;
    unsigned int copyBufferSize;
};

}

#endif