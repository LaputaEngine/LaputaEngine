#ifndef _LPTAD3DDYNAMICBUFFER_H_
#define _LPTAD3DDYNAMICBUFFER_H_

#include <d3d9.h>
#include "vertices/LptaVertexCollection.h"
#include "LptaD3DVertexBuffer.h"

namespace lpta_d3d
{

class LptaD3DDynamicBuffer
{
public:
    LptaD3DDynamicBuffer(LPDIRECT3DDEVICE9 d3ddev, lpta::VERTEX_TYPE vertexType,
        unsigned int maxVertices, unsigned int maxIndices);
    ~LptaD3DDynamicBuffer(void);

    lpta::VERTEX_TYPE GetVertexType(void) const;

    bool CanFit(const lpta::LptaVertexCollection &collection) const;

    bool AddVertices(lpta::LptaVertexCollection *collection);

private:
    lpta::VERTEX_TYPE vertexType;   

    unsigned int numVertices;
    unsigned int numIndices;

    unsigned int maxVertices;
    unsigned int maxIndices;

    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    LPDIRECT3DINDEXBUFFER9 indexBuffer;
};

}

#endif