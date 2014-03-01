#ifndef _LPTAD3DVERTEX_H_
#define _LPTAD3DVERTEX_H_

#include <d3d9.h>
#include "LptaD3DColorUtils.h"

#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
#define FVF_LVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

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

    lpta_d3d_utils::Color32Bit color;

    float tu;
    float tv;
} D3D_LVERTEX;

}

#endif