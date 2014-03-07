#ifndef _LPTAD3DSTATICBUFFERMANAGER_H_
#define _LPTAD3DSTATICBUFFERMANAGER_H_

#include "LptaResourceManager.h"
#include "vertices/LptaD3DStaticBufferResource.h"

namespace lpta_d3d
{

class LptaD3DStaticBufferManager : lpta::LptaResourceManager<LptaD3DStaticBufferResource>
{
public:
    LptaD3DStaticBufferManager(void);
    virtual ~LptaD3DStaticBufferManager(void);
};

}

#endif