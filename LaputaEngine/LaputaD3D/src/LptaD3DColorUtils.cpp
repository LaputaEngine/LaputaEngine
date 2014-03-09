#include <d3d9.h>
#include "LptaD3DColorUtils.h"

namespace lpta_d3d_utils
{


Color32Bit FloatToColor(float a, float r, float g, float b)
{
    Color32Bit color;
    color.dwColor = { D3DCOLOR_COLORVALUE(r, g, b, a) };
    return color;
}

}