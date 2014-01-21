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
	enum VECTOR_DIRECTION 
	{
		POSITIVE,
		NEGATIVE
	};
public:
    LptaVector(void);
    LptaVector(float x, float y, float z);
    ~LptaVector(void);

    inline float GetX(void) const;
    inline float GetY(void) const;
    inline float GetZ(void) const;

	inline void SetX(float x);
	inline void SetY(float y);
	inline void SetZ(float z);

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
    LptaVector operator *(float f) const;
    LptaVector operator +(const LptaVector &other) const;
    LptaVector operator -(const LptaVector &other) const;
	LptaVector Cross(const LptaVector &other) const;
private:
    typedef struct VECTOR_TYPE VECTOR;
    VECTOR vector;
};
typedef LptaVector COORDINATE;



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

#endif