#include "vertices/LptaVertexCollection.h"
#include "vertices/LptaUUVertexCollection.h"
#include "vertices/LptaULVertexCollection.h"
#include "vertices/LptaD3DVertexCollectionVisitor.h"

namespace lpta_d3d
{

LptaD3DVertexCollectionVisitor::LptaD3DVertexCollectionVisitor(void)
{
}

LptaD3DVertexCollectionVisitor::~LptaD3DVertexCollectionVisitor(void)
{
}

void LptaD3DVertexCollectionVisitor::Visit(lpta::LptaVertexCollection *collection)
{
    // log error
}

void LptaD3DVertexCollectionVisitor::Visit(lpta::LptaUUVertexCollection *collection)
{
    for (const lpta::UU_VERTEX &vertex : collection->GetVertices()) {
        // todo 
        transforms.push_back(LptaD3DStaticBuffer());
    }
}

void LptaD3DVertexCollectionVisitor::Visit(lpta::LptaULVertexCollection *collection)
{
    for (const lpta::UL_VERTEX &vertex : collection->GetVertices()) {
        // todo
        transforms.push_back(LptaD3DStaticBuffer());
    }
}

const std::vector<LptaD3DStaticBuffer> &LptaD3DVertexCollectionVisitor::GetTransforms(void) const
{
    return transforms;
}

}