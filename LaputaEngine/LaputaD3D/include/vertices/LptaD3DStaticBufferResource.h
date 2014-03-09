#ifndef _LPTAD3DSTATICBUFFERRESOURCE_H_
#define _LPTAD3DSTATICBUFFERRESOURCE_H_

#include <memory>
#include "LptaResource.h"
#include "vertices/LptaD3DStaticBuffer.h"

namespace lpta_d3d
{

class LptaD3DStaticBufferResource : public lpta::LptaResource
{
public:
    typedef LptaResource::ID STATIC_BUFFER_ID;

public:
    LptaD3DStaticBufferResource(STATIC_BUFFER_ID id, LptaD3DStaticBuffer *buffer);
    virtual ~LptaD3DStaticBufferResource(void);

    LptaD3DStaticBuffer *GetBuffer(void) const { return buffer.get(); }

private:
    std::shared_ptr<LptaD3DStaticBuffer> buffer;
};

}

#endif