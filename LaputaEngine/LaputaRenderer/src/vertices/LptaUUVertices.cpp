#include "vertices/LptaUUVertices.h"

namespace lpta
{

LptaUUVertices::LptaUUVertices(void) : LptaVertices(VERTEX_TYPE::VT_UU)
{
}

LptaUUVertices::~LptaUUVertices(void)
{
}

unsigned int LptaUUVertices::GetNumVertices(void) const
{
    return vertices.size();
}

void LptaUUVertices::Accept(LptaVerticesVisitor *visitor)
{
    visitor->Visit(this);
}

void LptaUUVertices::AddVertex(const UU_VERTEX &vertex)
{
    vertices.push_back(vertex);
}

const std::vector<UU_VERTEX> &LptaUUVertices::GetVertices(void) const
{
    return vertices;
}

}