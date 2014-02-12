#ifndef _LPTAQUAT_H_
#define _LPTAQUAT_H_

namespace lpta_3d
{

class LptaMatrix;

class LptaQuat
{
public:
    LptaQuat(void);
    LptaQuat(float w, float x, float y, float z);

    static LptaQuat MakeFromEuler(float pitch, float yaw, float roll);

    inline float GetW(void) const;
    inline float GetX(void) const;
    inline float GetY(void) const;
    inline float GetZ(void) const;

    LptaMatrix GetMatrix(void) const;

    LptaQuat operator *(const LptaQuat &quat) const;
    void operator *=(const LptaQuat &quat);
private:
    float w;
    float x;
    float y;
    float z;
};

float LptaQuat::GetW(void) const
{
    return w;
}

float LptaQuat::GetX(void) const
{
    return x;
}

float LptaQuat::GetY(void) const
{
    return y;
}

float LptaQuat::GetZ(void) const
{
    return z;
}

}

#endif