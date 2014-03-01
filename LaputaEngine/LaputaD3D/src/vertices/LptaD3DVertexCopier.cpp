#include "LptaD3DColorUtils.h"
#include "vertices/LptaD3DVertex.h"
#include "vertices/LptaVertexCollection.h"
#include "vertices/LptaUUVertexCollection.h"
#include "vertices/LptaULVertexCollection.h"
#include "vertices/LptaD3DVertexCopier.h"

namespace lpta_d3d
{
inline bool HasValidTargetBuffer(void *buffer);

LptaD3DVertexCopier::LptaD3DVertexCopier(lpta::LptaVertexCollection *collection) : 
    copyBuffer(NULL), stride(0), collection(collection)
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

void LptaD3DVertexCopier::CopyToBuffer(void *buffer)
{
    this->copyBuffer = buffer;
    collection->Accept(this);
    this->copyBuffer = NULL;
}

void LptaD3DVertexCopier::Visit(lpta::LptaVertexCollection *collection)
{
    // log error
}

void LptaD3DVertexCopier::Visit(lpta::LptaUUVertexCollection *collection)
{
    if (!HasValidTargetBuffer(copyBuffer)) {
        // log error
        return;
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
    if (!HasValidTargetBuffer(copyBuffer)) {
        // log error
        return;
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

bool HasValidTargetBuffer(void *buffer)
{
    return NULL != buffer;
}

}