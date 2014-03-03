#ifndef _LPTAVECTOR_H_
#define _LPTAVECTOR_H_

#include "LptaMatrix.h"
#include "errors/InvalidDimension.h"

namespace
{
    typedef struct VECTOR_TYPE
    {
        float x;
        float y;
        float z;
        float w;
    } VECTOR;
}

namespace lpta_3d
{

class LptaVector
{
protected:
    static bool sseCapable;
public:
    enum VECTOR_DIRECTION 
    {
        POSITIVE,
        NEGATIVE
    };
    enum DIMENSION
    {
        X,
        Y,
        Z
    };
public:
    LptaVector(void);
    LptaVector(float x, float y, float z);
    virtual ~LptaVector(void);

    inline float GetDimension(DIMENSION dim) const;
    inline float GetX(void) const;
    inline float GetY(void) const;
    inline float GetZ(void) const;

    inline void SetDimension(DIMENSION dim, float value);
    virtual inline void SetX(float x);
    virtual inline void SetY(float y);
    virtual inline void SetZ(float z);

    float Length(void) const;
    float LengthSquared(void) const;
    bool IsNormal(void) const;

    void Normalize(void);

    void operator +=(const LptaVector &other);
    void operator -=(const LptaVector &other);
    void operator *=(const LptaVector &other);
    void operator /=(const LptaVector &other);

    float operator *(const LptaVector &other) const;
    LptaVector operator *(const LptaMatrix &m) const;
    LptaVector operator *(float multiplier) const;
    LptaVector operator /(float divisor) const;
    LptaVector operator +(const LptaVector &other) const;
    LptaVector operator -(const LptaVector &other) const;
    LptaVector Cross(const LptaVector &other) const;

private:
    VECTOR vector;
};
typedef LptaVector POINT;


float LptaVector::GetDimension(DIMENSION dim) const
{
    switch (dim) {
    case X:
        return GetX();
    case Y:
        return GetY();
    case Z:
        return GetZ();
    default:
        throw InvalidDimension();
    }
}
float LptaVector::GetX(void) const
{
    return vector.x;
}
float LptaVector::GetY(void) const
{
    return vector.y;
}
float LptaVector::GetZ(void) const
{
    return vector.z;
}

void LptaVector::SetDimension(DIMENSION dim, float value)
{
    switch (dim) {
    case X:
        SetX(value);
        break;
    case Y:
        SetY(value);
        break;
    case Z:
        SetZ(value);
        break;
    default:
        throw InvalidDimension();
    }
}
void LptaVector::SetX(float x)
{
    vector.x = x;
}
void LptaVector::SetY(float y)
{
    vector.y = y;
}
void LptaVector::SetZ(float z)
{
    vector.z = z;
}

}

#endif