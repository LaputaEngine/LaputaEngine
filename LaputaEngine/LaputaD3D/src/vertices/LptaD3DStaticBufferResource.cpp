#include "vertices/LptaD3DStaticBufferResource.h"

namespace lpta_d3d
{

LptaD3DStaticBufferResource::LptaD3DStaticBufferResource(STATIC_BUFFER_ID id, 
    LptaD3DStaticBuffer *buffer) : LptaResource(id), 
    buffer(std::shared_ptr<LptaD3DStaticBuffer>(buffer))
{
}

LptaD3DStaticBufferResource::~LptaD3DStaticBufferResource(void)
{
}

}