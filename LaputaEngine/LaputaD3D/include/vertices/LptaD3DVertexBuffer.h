#ifndef _LPTAD3DVERTEXBUFFER_H_
#define _LPTAD3DVERTEXBUFFER_H_

#include <d3d9.h>

namespace lpta_d3d
{

class LptaD3DVertexBuffer
{
public:
    virtual ~LptaD3DVertexBuffer(void);

protected:
    LptaD3DVertexBuffer(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DINDEXBUFFER9 indexBuffer);
    LptaD3DVertexBuffer(const LptaD3DVertexBuffer &copyTarget);

protected:
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    LPDIRECT3DINDEXBUFFER9 indexBuffer;
};

}

#endif