#include "vertices/LptaUUVertexCollection.h"

namespace lpta
{

LptaUUVertexCollection::LptaUUVertexCollection(void) : LptaVertexCollection(VERTEX_TYPE::VT_UU)
{
}

LptaUUVertexCollection::~LptaUUVertexCollection(void)
{
}

unsigned int LptaUUVertexCollection::GetNumVertices(void) const
{
    return vertices.size();
}

void LptaUUVertexCollection::Accept(LptaVertexCollectionVisitor *visitor)
{
    visitor->Visit(this);
}

void LptaUUVertexCollection::AddVertex(const UU_VERTEX &vertex)
{
    vertices.push_back(vertex);
}

const std::vector<UU_VERTEX> &LptaUUVertexCollection::GetVertices(void) const
{
    return vertices;
}

}