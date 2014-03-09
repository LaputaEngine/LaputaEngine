#include "LptaD3DColorUtils.h"
#include "vertices/LptaD3DVertex.h"
#include "vertices/LptaVertices.h"
#include "vertices/LptaUUVertices.h"
#include "vertices/LptaULVertices.h"
#include "vertices/errors/D3DCopierInvalidTargetBuffer.h"
#include "vertices/LptaD3DVertexCopier.h"

namespace lpta_d3d
{

LptaD3DVertexCopier::LptaD3DVertexCopier(lpta::LptaVertices *collection) : 
    copyBuffer(nullptr), copyBufferSize(0), collection(collection)
{
}

LptaD3DVertexCopier::~LptaD3DVertexCopier(void)
{
}

lpta::VERTEX_TYPE LptaD3DVertexCopier::GetVertexType(void) const
{
    return collection->GetType();
}

unsigned int LptaD3DVertexCopier::Stride(void) const
{
    return ToStride(collection->GetType());
}

unsigned int LptaD3DVertexCopier::NumVertices(void) const
{
    return collection->GetNumVertices();
}

unsigned int LptaD3DVertexCopier::ByteSize(void) const
{
    return NumVertices() * Stride();
}

LptaD3DVertexCopier::COPY_RESULT LptaD3DVertexCopier::CopyToBuffer(
    void *buffer, 
    unsigned int bufferSize)
{
    this->copyBuffer = buffer;
    this->copyBufferSize = bufferSize;
    try {
        collection->Accept(this);
        this->copyBuffer = nullptr;
        this->copyBufferSize = 0;
        return COPY_RESULT::SUCCESS;
    }
    catch (D3DCopierInvalidTargetBuffer)
    {
        // log error
        this->copyBuffer = nullptr;
        this->copyBufferSize = 0;
        return COPY_RESULT::FAILURE;
    }
}
bool BufferLargeEnough(unsigned int byteSize, unsigned int bufferSize)
{
    return byteSize <= bufferSize;
}

void LptaD3DVertexCopier::Visit(lpta::LptaVertices *collection)
{
    // log error
}

void LptaD3DVertexCopier::Visit(lpta::LptaUUVertices *collection)
{
    if (!HasValidCopyBuffer<D3D_VERTEX>()) {
        // log error

        throw D3DCopierInvalidTargetBuffer();
    }
    D3D_VERTEX *buffer = static_cast<D3D_VERTEX *>(copyBuffer);
    for (unsigned int i = 0; i < NumVertices(); ++i) {
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

void LptaD3DVertexCopier::Visit(lpta::LptaULVertices *collection)
{
    if (!HasValidCopyBuffer<D3D_LVERTEX>()) {

        // log error
        throw D3DCopierInvalidTargetBuffer();
    }
    D3D_LVERTEX *buffer = static_cast<D3D_LVERTEX *>(copyBuffer);
    for (unsigned int i = 0; i < NumVertices(); ++i) {
        const auto &vertex = collection->GetVertices().at(i);
        // todo
        buffer[i].x = vertex.coordinate.GetX();
        buffer[i].y = vertex.coordinate.GetY();
        buffer[i].z = vertex.coordinate.GetZ();
        buffer[i].rhw = 1.0f;

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
bool LptaD3DVertexCopier::HasValidCopyBuffer(void) const
{
    // defensive assertion, ByteSize should return the proper size of buffer to allocate,
    // but recalculate in visitor method to guarantee that the copy buffer is large enough
    return nullptr != copyBuffer &&
        copyBufferSize >= (sizeof(T) * NumVertices());
}

}