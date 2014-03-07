#ifndef _LPTAD3DSTATICBUFFERRESOURCE_H_
#define _LPTAD3DSTATICBUFFERRESOURCE_H_

#include "LptaResource.h"
#include "vertices/LptaD3DStaticBuffer.h"

namespace lpta_d3d
{

class LptaD3DStaticBufferResource : public LptaResource
{
public:
    typedef LptaResource::ID STATIC_BUFFER_ID;

public:
    LptaD3DStaticBufferResource(STATIC_BUFFER_ID id, const LptaD3DStaticBuffer &buffer);
    virtual ~LptaD3DStaticBufferResource(void);

    const LptaD3DStaticBuffer &GetBuffer(void) const;

private:
    private LptaD3DStaticBuffer buffer;
};

}

#endif