#ifndef _LPTAD3DCOLORUTILS_H_
#define _LPTAD3DCOLORUTILS_H_

#include <Windows.h>

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2
#define ALPHA_CHANNEL 3

#define MAX_ARGB 255

namespace lpta_d3d_utils
{

struct Color32Bit
{
    union
    {
        struct
        {
            unsigned char b;
            unsigned char g;
            unsigned char r;
            unsigned char a;
        };
        DWORD dwColor;
    };
};

Color32Bit FloatToColor(float a, float r, float g, float b);

}

#endif