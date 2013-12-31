#ifndef _LPTAVECTOR_H_
#define _LPTAVECTOR_H_

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

    float GetX(void);
    float GetY(void);
    float GetZ(void);

    float Length(void) const;

    void operator +=(const LptaVector &other);
    void operator -=(const LptaVector &other);
    void operator *=(const LptaVector &other);
    void operator /=(const LptaVector &other);

    float operator *(const LptaVector &other) const;
    LptaVector operator *(float f) const;
    LptaVector operator +(const LptaVector &other) const;
    LptaVector operator -(const LptaVector &other) const;
private:
    typedef struct VECTOR_TYPE VECTOR;
    VECTOR vector;
};

#endif