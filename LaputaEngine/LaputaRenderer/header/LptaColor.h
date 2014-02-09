#ifndef _LPTACOLOR_H_
#define _LPTACOLOR_H_

namespace lpta
{

class LptaColor
{
protected:
    static const float DEFAULT_CHANNEL_VALUE;
    static const unsigned int NUM_CHANNELS = 4;
    static const unsigned int RED = 0;
    static const unsigned int GREEN = 1;
    static const unsigned int BLUE = 2;
    static const unsigned int ALPHA = 3;
public:
    LptaColor(void);
    LptaColor(float red, float green, float blue, float alpha);
    ~LptaColor(void);

    inline float GetRed(void) const;
    inline float GetGreen(void) const;
    inline float GetBlue(void) const;
    inline float GetAlpha(void) const;
private:
    float channels[4];
};

float LptaColor::GetRed(void) const
{
    return channels[RED];
}

float LptaColor::GetGreen(void) const
{
    return channels[GREEN];
}

float LptaColor::GetBlue(void) const
{
    return channels[BLUE];
}

float LptaColor::GetAlpha(void) const
{
    return channels[ALPHA];
}

}

#endif