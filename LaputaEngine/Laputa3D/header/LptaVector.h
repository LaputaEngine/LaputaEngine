#ifndef _LPTAVECTOR_H_
#define _LPTAVECTOR_H_

#include "LptaMatrix.h"

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

class LptaVector
{
protected:
    static bool sseCapable;
public:
    LptaVector(void);
    LptaVector(float x, float y, float z);
    ~LptaVector(void);

    float GetX(void) const;
    float GetY(void) const;
    float GetZ(void) const;

    float Length(void) const;
	bool IsNormal(void) const;

    void Normalize(void);

    void operator +=(const LptaVector &other);
    void operator -=(const LptaVector &other);
    void operator *=(const LptaVector &other);
    void operator /=(const LptaVector &other);

    float operator *(const LptaVector &other) const;
    LptaVector operator *(const LPTA_MATRIX m) const;
    LptaVector operator *(float f) const;
    LptaVector operator +(const LptaVector &other) const;
    LptaVector operator -(const LptaVector &other) const;
	LptaVector Cross(const LptaVector &other) const;
private:
    typedef struct VECTOR_TYPE VECTOR;
    VECTOR vector;
};

typedef LptaVector COORDINATE;

#endif