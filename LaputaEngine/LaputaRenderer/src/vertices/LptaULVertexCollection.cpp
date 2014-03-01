#include "vertices/LptaULVertexCollection.h"

namespace lpta
{

LptaULVertexCollection::LptaULVertexCollection(void) : LptaVertexCollection(VERTEX_TYPE::VT_UL)
{
}

LptaULVertexCollection::~LptaULVertexCollection(void)
{
}

unsigned int LptaULVertexCollection::GetNumVertices(void) const
{
    return vertices.size();
}

void LptaULVertexCollection::Accept(LptaVertexCollectionVisitor *visitor)
{
    return visitor->Visit(this);
}

void LptaULVertexCollection::AddVertex(const UL_VERTEX &vertex)
{
    vertices.push_back(vertex);
}

const std::vector<UL_VERTEX> &LptaULVertexCollection::GetVertices(void) const
{
    return vertices;
}

}