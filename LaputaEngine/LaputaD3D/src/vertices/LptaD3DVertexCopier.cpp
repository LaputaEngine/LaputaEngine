#include "LptaD3DColorUtils.h"
#include "vertices/LptaD3DVertex.h"
#include "vertices/LptaVertexCollection.h"
#include "vertices/LptaUUVertexCollection.h"
#include "vertices/LptaULVertexCollection.h"
#include "vertices/errors/D3DCopierInvalidTargetBuffer.h"
#include "vertices/LptaD3DVertexCopier.h"

namespace lpta_d3d
{
template <class T>
inline bool BufferLargeEnough(unsigned int bufferSize, unsigned int numCount);
inline bool HasValidTargetBuffer(void *buffer);

LptaD3DVertexCopier::LptaD3DVertexCopier(lpta::LptaVertexCollection *collection) : 
    copyBuffer(NULL), copyBufferSize(0), stride(0), collection(collection)
{
    using lpta::VERTEX_TYPE;

    switch (collection->GetType()) {
    case VERTEX_TYPE::VT_UU:
        stride = sizeof(D3D_VERTEX);
        break;
    case VERTEX_TYPE::VT_UL:
        stride = sizeof(D3D_LVERTEX);
        break;
    default:
        // log error
        ;
    }
}

LptaD3DVertexCopier::~LptaD3DVertexCopier(void)
{
}

unsigned int LptaD3DVertexCopier::GetStride(void) const
{
    return stride;
}

unsigned int LptaD3DVertexCopier::GetNumVertices(void) const
{
    return collection->GetNumVertices();
}

unsigned int LptaD3DVertexCopier::ByteSize(void) const
{
    return GetNumVertices() * GetStride();
}

LptaD3DVertexCopier::COPY_RESULT LptaD3DVertexCopier::CopyToBuffer(
    void *buffer, 
    unsigned int bufferSize)
{
    this->copyBuffer = buffer;
    this->copyBufferSize = bufferSize;
    try {
        collection->Accept(this);
        this->copyBuffer = NULL;
        this->copyBufferSize = 0;
        return COPY_RESULT::SUCCESS;
    }
    catch (D3DCopierInvalidTargetBuffer)
    {
        // log error
        this->copyBuffer = NULL;
        this->copyBufferSize = 0;
        return COPY_RESULT::FAILURE;
    }
}
bool BufferLargeEnough(unsigned int byteSize, unsigned int bufferSize)
{
    return byteSize <= bufferSize;
}

void LptaD3DVertexCopier::Visit(lpta::LptaVertexCollection *collection)
{
    // log error
}

void LptaD3DVertexCopier::Visit(lpta::LptaUUVertexCollection *collection)
{
    if (!HasValidTargetBuffer(copyBuffer) || 
        !BufferLargeEnough<D3D_VERTEX>(copyBufferSize, GetNumVertices())) {

        throw D3DCopierInvalidTargetBuffer();
    }
    D3D_VERTEX *buffer = static_cast<D3D_VERTEX *>(copyBuffer);
    for (unsigned int i = 0; i < GetNumVertices(); ++i) {
        const auto &vertex = collection->GetVertices().at(i);
        // todo
        buffer[i].x = vertex.coordinate.GetX();
        buffer[i].y = vertex.coordinate.GetY();
        buffer[i].z = vertex.coordinate.GetZ();

        buffer[i].normal[0] = vertex.normal.GetX();
        buffer[i].normal[1] = vertex.normal.GetY();
        buffer[i].normal[2] = vertex.normal.GetZ();

        buffer[i].tu = vertex.tu;
        buffer[i].tv = vertex.tv;
    }
}

void LptaD3DVertexCopier::Visit(lpta::LptaULVertexCollection *collection)
{
    if (!HasValidTargetBuffer(copyBuffer) ||
        !BufferLargeEnough<D3D_LVERTEX>(copyBufferSize, GetNumVertices())) {

        // log error
        throw D3DCopierInvalidTargetBuffer();
    }
    D3D_LVERTEX *buffer = static_cast<D3D_LVERTEX *>(copyBuffer);
    for (unsigned int i = 0; i < GetNumVertices(); ++i) {
        const auto &vertex = collection->GetVertices().at(i);
        // todo
        buffer[i].x = vertex.coordinate.GetX();
        buffer[i].y = vertex.coordinate.GetY();
        buffer[i].z = vertex.coordinate.GetZ();

        buffer[i].color = lpta_d3d_utils::FloatToColor(
            vertex.color.GetAlpha(),
            vertex.color.GetRed(),
            vertex.color.GetGreen(),
            vertex.color.GetBlue()
        );

        buffer[i].tu = vertex.tu;
        buffer[i].tv = vertex.tv;
    }
}

template <class T>
bool BufferLargeEnough<T>(unsigned int bufferSize, unsigned int numVertices)
{
    return bufferSize >= (sizeof(T) * numVertices);
}
bool HasValidTargetBuffer(void *buffer)
{
    return NULL != buffer;
}

}