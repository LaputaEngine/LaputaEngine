#include "LptaD3DColorUtils.h"

namespace lpta_d3d_utils
{

Color24Bit FloatToColor(float r, float g, float b)
{
    Color24Bit color = {
        (unsigned char)(MAX_ARGB * r),
        (unsigned char)(MAX_ARGB * g),
        (unsigned char)(MAX_ARGB * b)
    };
    return color;
}

Color32Bit FloatToColor(float a, float r, float g, float b)
{
    Color32Bit color = {
        (unsigned char)(MAX_ARGB * a),
        (unsigned char)(MAX_ARGB * r),
        (unsigned char)(MAX_ARGB * g),
        (unsigned char)(MAX_ARGB * b)
    };
    return color;
}

}