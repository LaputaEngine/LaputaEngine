#include "vertices/LptaVertexCollection.h"

namespace lpta
{

LptaVertexCollection::LptaVertexCollection(VERTEX_TYPE vType) : vertexType(vType)
{
}

LptaVertexCollection::~LptaVertexCollection(void)
{
}

VERTEX_TYPE LptaVertexCollection::GetType(void) const
{
    return vertexType;
}

}