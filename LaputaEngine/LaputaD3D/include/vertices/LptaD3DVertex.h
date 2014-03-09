#ifndef _LPTAD3DVERTEX_H_
#define _LPTAD3DVERTEX_H_

#include <d3d9.h>
#include "vertices/LptaVertices.h"
#include "LptaD3DColorUtils.h"

#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2)
// todo get rid of the RHW and use the rendering device's world transform
#define FVF_LVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2)

#define INVALID_STRIDE 0

namespace lpta_d3d
{

typedef struct D3D_VERTEX_TYPE
{
    float x;
    float y;
    float z;

    float normal[3];

    float tu;
    float tv;
} D3D_VERTEX;

typedef struct D3D_LVERTEX_TYPE
{
    float x;
    float y;
    float z;
    float rhw;

    lpta_d3d_utils::Color32Bit color;

    float tu;
    float tv;
} D3D_LVERTEX;

inline unsigned int ToStride(lpta::VERTEX_TYPE vertexType)
{
    using lpta::VERTEX_TYPE;

    switch (vertexType) {
    case VERTEX_TYPE::VT_UU:
        return sizeof(D3D_VERTEX);
    case VERTEX_TYPE::VT_UL:
        return sizeof(D3D_LVERTEX);
    default:
        // log error
        return INVALID_STRIDE;
    }
}

inline DWORD ToFVF(lpta::VERTEX_TYPE vertexType)
{
    using lpta::VERTEX_TYPE;

    switch (vertexType) {
    case VERTEX_TYPE::VT_UU:
        return FVF_VERTEX;
    case VERTEX_TYPE::VT_UL:
        return FVF_LVERTEX;
    default:
        // log error
        return 0;
    }
}

}

#endif