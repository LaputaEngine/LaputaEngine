#include <Windows.h>
#include <math.h>
#include "LptaVector.h"

#if LPTA_MATRIX_ROWS != 4 || LPTA_MATRIX_COLUMNS != 4
#error LptaVector only works with 4x4 matrices
#endif

bool CheckSSECapability(void);

bool LptaVector::sseCapable = CheckSSECapability();
bool CheckSSECapability(void)
{
    bool hasSSE = false;
    __try {
        _asm {
            MOV        eax, 1
            CPUID
            TEST    edx, 02000000h
            JZ        _NOSSE
            MOV        [hasSSE], 1
        _NOSSE:
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        ; // no handling necessary
    }
    return hasSSE;
}

LptaVector::LptaVector(void)
{
    LptaVector(0.0f, 0.0f, 0.0f);
}

LptaVector::LptaVector(float x, float y, float z)
{
    vector.x = x;
    vector.y = y;
    vector.z = z;
    vector.w = 1.0f;
}

LptaVector::~LptaVector(void)
{
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

float LptaVector::Length(void) const
{
    if (sseCapable) {
        float length;
        float *lengthPtr = &length;
        VECTOR v = vector;
        v.w = 0;
        VECTOR *vPtr = &v;
        _asm {
            MOV     ecx, lengthPtr
            MOV     esi, vPtr
            MOVUPS  XMM0, [esi]
            MULPS   XMM0, XMM0      ; [x*x, y*y, z*z, w*w]
            MOVAPS  XMM1, XMM0
            SHUFPS  XMM1, XMM1, 4Eh ; [z*z, w*w, x*x, y*y]
            ADDPS   XMM0, XMM1      ; [x*x + z*z]
            SHUFPS  XMM1, XMM1, 00h ; [y*y, y*y, y*y, y*y]
            ADDPS   XMM0, XMM1      ; [x*x + z*z + y*y]
            SQRTSS  XMM0, XMM0
            MOVSS   [ecx], XMM0
        }
        return length;
    }
    else {
        return sqrt(vector.x * vector.x +
            vector.y + vector.y +
            vector.z + vector.z);
    }
}

void LptaVector::Normalize(void)
{
    
    if (sseCapable) {
        VECTOR *vPtr = &vector;
        vector.w = 0.0f;
        _asm {
            MOV     esi, vPtr
            MOVUPS  XMM0, [esi]
            MOVAPS  XMM2, XMM0
            MULPS   XMM0, XMM0      ; [x*x, y*y, z*z, w*w]
            MOVAPS  XMM1, XMM0
            SHUFPS  XMM1, XMM1, 4Eh ; [z*z, w*w, x*x, y*y]
            ADDPS   XMM0, XMM1      ; [x*x + z*z, y*y + w*w, z*z + x*x, w*w + y*y]
            MOVAPS  XMM1, XMM0
            SHUFPS  XMM1, XMM1, 11h ; [w*w + y*y, z*z + x*x, w*w + y*y, z*z + x*x]
            ADDPS   XMM0, XMM1      ; [x*x + y*y + z*z + w*w x 4]

            RSQRTPS XMM0, XMM0
            MULPS   XMM0, XMM2
            MOVUPS  [esi], XMM0
        }
        // TODO figure out why
        vector.w = 1.0f;
    }
    else {
        float length = Length();
        vector.x /= length;
        vector.y /= length;
        vector.z /= length;
    }
}

void LptaVector::operator +=(const LptaVector &other)
{
    vector.x += other.vector.x;
    vector.y += other.vector.y;
    vector.z += other.vector.z;
}

void LptaVector::operator -=(const LptaVector &other)
{
    vector.x -= other.vector.x;
    vector.y -= other.vector.y;
    vector.z -= other.vector.z;
}

void LptaVector::operator *=(const LptaVector &other)
{
    vector.x *= other.vector.x;
    vector.y *= other.vector.y;
    vector.z *= other.vector.z;
}

void LptaVector::operator /=(const LptaVector &other)
{
    vector.x /= other.vector.x;
    vector.y /= other.vector.y;
    vector.z /= other.vector.z;
}

float LptaVector::operator *(const LptaVector &other) const
{
    return (vector.x * other.vector.x +
        vector.y * other.vector.y +
        vector.z * other.vector.z);
}

LptaVector LptaVector::operator *(const LptaMatrix &m) const
{
    LptaVector result;
    VECTOR *v = &result.vector;
    if (sseCapable) {
        const VECTOR *vPtr = &vector;
        const LptaMatrix::MATRIX *mPtr = &m.GetMatrix();
        _asm {
            MOV     ecx, vPtr
            MOV     edx, mPtr
            MOV     eax, v
            // TODO finish
        }
    }
    else {
        for (unsigned int row = 0; row < LPTA_MATRIX_ROWS; ++row) {
            float *vRow = ((float *)v) + row;
            *vRow = (vector.x * m.Get(row, 0)) + 
                (vector.y * m.Get(row, 1)) +
                (vector.z * m.Get(row, 2)) +
                (vector.w * m.Get(row, 3));
        }
    }
    return result;
}

LptaVector LptaVector::operator *(float f) const
{
    return LptaVector(vector.x * f, vector.y * f, vector.z * f);
}

LptaVector LptaVector::operator +(const LptaVector &other) const
{
    LptaVector result = *this;
    result += other;
    return result;
}

LptaVector LptaVector::operator -(const LptaVector &other) const
{
    LptaVector result = *this;
    result -= other;
    return result;
}