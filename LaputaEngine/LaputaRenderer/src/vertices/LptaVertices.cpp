#include "vertices/LptaVertices.h"

namespace lpta
{

LptaVertices::LptaVertices(VERTEX_TYPE vType) : vertexType(vType)
{
}

LptaVertices::~LptaVertices(void)
{
}

VERTEX_TYPE LptaVertices::GetType(void) const
{
    return vertexType;
}

}