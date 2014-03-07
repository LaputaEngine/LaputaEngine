#ifndef _LPTAD3DDYNAMICBUFFER_H_
#define _LPTAD3DDYNAMICBUFFER_H_

#include <d3d9.h>
#include "vertices/LptaVertices.h"
#include "vertices/LptaIndices.h"

namespace lpta_d3d
{

class LptaD3DDynamicBuffer
{
public:
    // copy is disallowed because each instance should have unique ownership to
    // the allocated dx9 buffers
    LptaD3DDynamicBuffer(const LptaD3DDynamicBuffer &copy) = delete;

    LptaD3DDynamicBuffer(LPDIRECT3DDEVICE9 d3ddev, lpta::VERTEX_TYPE vertexType,
        unsigned int maxVertices, unsigned int maxIndices);
    ~LptaD3DDynamicBuffer(void);

    lpta::VERTEX_TYPE GetVertexType(void) const;

    bool CanFit(const lpta::LptaVertices &vertices, const lpta::INDICES &indices) const;
    bool CanFit(const lpta::LptaVertices &vertices) const;

    bool Add(lpta::LptaVertices *vertices, const lpta::INDICES &indices);
    bool AddVertices(lpta::LptaVertices *vertices);

private:
    bool LockedBuffers(void **vertexWriteBuffer, unsigned int vertexByteSize,
        DWORD **indexWriteBuffer, unsigned int indexByteSize, DWORD lockFlag);

private:
    lpta::VERTEX_TYPE vertexType;   

    unsigned int numVertices;
    unsigned int numIndices;

    const unsigned int maxVertices;
    const unsigned int maxIndices;

    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    LPDIRECT3DINDEXBUFFER9 indexBuffer;
};

}

#endif