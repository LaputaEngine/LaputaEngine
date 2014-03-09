#ifndef _LPTAD3DSTATICBUFFER_H_
#define _LPTAD3DSTATICBUFFER_H_

#include <d3d9.h>
#include "LptaSkin.h"
#include "vertices/LptaVertices.h"
#include "vertices/LptaIndices.h"

namespace lpta_d3d
{

class LptaD3DStaticBuffer
{
public:
    LptaD3DStaticBuffer(const LptaD3DStaticBuffer &copy) = delete;

    LptaD3DStaticBuffer(LPDIRECT3DDEVICE9 d3ddev, 
        lpta::LptaVertices *vertices, const lpta::INDICES &indices, 
        lpta::LptaSkin::SKIN_ID skinId, bool useShader=true);
    ~LptaD3DStaticBuffer(void);

private:
    const lpta::VERTEX_TYPE vertexType;

    const lpta::LptaSkin::SKIN_ID skinId;

    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    LPDIRECT3DINDEXBUFFER9 indexBuffer;
};

}

#endif