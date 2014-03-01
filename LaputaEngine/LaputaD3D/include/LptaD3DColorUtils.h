#ifndef _LPTAD3DCOLORUTILS_H_
#define _LPTAD3DCOLORUTILS_H_

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2
#define ALPHA_CHANNEL 3

#define MAX_ARGB 255

namespace lpta_d3d_utils
{

struct Color24Bit
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct Color32Bit
{
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

Color24Bit FloatToColor(float r, float g, float b);
Color32Bit FloatToColor(float a, float r, float g, float b);

}

#endif