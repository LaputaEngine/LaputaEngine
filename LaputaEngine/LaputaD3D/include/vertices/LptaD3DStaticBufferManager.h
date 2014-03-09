#ifndef _LPTAD3DSTATICBUFFERMANAGER_H_
#define _LPTAD3DSTATICBUFFERMANAGER_H_

#include "LptaResourceManager.h"
#include "vertices/LptaD3DStaticBufferResource.h"

namespace lpta_d3d
{

struct NoSuchBuffer {};

class LptaD3DStaticBufferManager : lpta::LptaResourceManager<LptaD3DStaticBufferResource>
{
public:
    LptaD3DStaticBufferManager(LPDIRECT3DDEVICE9 d3ddev);
    virtual ~LptaD3DStaticBufferManager(void);

    LptaD3DStaticBufferResource::ID AddBuffer(LptaD3DStaticBuffer *buffer);

    LptaD3DStaticBuffer *GetStaticBuffer(LptaD3DStaticBufferResource::ID id) const;
};

}

#endif