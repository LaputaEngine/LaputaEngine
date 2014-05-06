#include "vertices/LptaULVertices.h"

namespace lpta
{

LptaULVertices::LptaULVertices(void) : LptaVertices(VERTEX_TYPE::VT_UL)
{
}

LptaULVertices::~LptaULVertices(void)
{
}

unsigned int LptaULVertices::GetNumVertices(void) const
{
    return vertices.size();
}

void LptaULVertices::Accept(LptaVerticesVisitor *visitor) const
{
    return visitor->Visit(this);
}

void LptaULVertices::AddVertex(const UL_VERTEX &vertex)
{
    vertices.push_back(vertex);
}

const std::vector<UL_VERTEX> &LptaULVertices::GetVertices(void) const
{
    return vertices;
}

}