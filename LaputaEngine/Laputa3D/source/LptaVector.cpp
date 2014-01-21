#include <Windows.h>
#include <math.h>
#include "Lpta3D.h"
#include "LptaVector.h"

#if LPTA_MATRIX_ROWS != 4 || LPTA_MATRIX_COLUMNS != 4
#error LptaVector only works with 4x4 matrices
#endif

// todo: should think about getting rid of this
__declspec(align(16)) const float RSQRT_CONST[4] = { 3.0f, 3.0f, 3.0f, 3.0f };
__declspec(align(16)) const float RSQRT_DIV[4] = { 2.0f, 2.0f, 2.0f, 2.0f };

bool CheckSSECapability(void);

bool LptaVector::sseCapable = CheckSSECapability();
bool CheckSSECapability(void)
{
    bool hasSSE = false;
    __try {
        _asm {
            MOV		eax, 1
            CPUID
            TEST    edx, 02000000h
            JZ		_NOSSE
            MOV		[hasSSE], 1
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
			ADDPS   XMM0, XMM1		; [x*x + z*z, y*y + w*w, z*z + x*x, w*w + y*y]
			SHUFPS  XMM1, XMM1, 0FFh; [w*w + y*y, w*w + y*y, w*w + y*y, w*w + y*y]
            ADDPS   XMM0, XMM1      ; [x*x + z*z + y*y]
            SQRTSS  XMM0, XMM0
			MOVSS[ecx], XMM0
        }
        return length;
    }
    else {
        return sqrt(vector.x * vector.x +
            vector.y * vector.y +
            vector.z * vector.z);
    }
}

float LptaVector::LengthSquared(void) const
{
	return (vector.x * vector.x) +
		(vector.y * vector.y) +
		(vector.z * vector.z);
}

bool LptaVector::IsNormal(void) const
{
	const float normal_length = 1.0f;
	const float length = Length();
	return fabs((length - normal_length) / length) < LPTA_EPSILON;
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

            RSQRTPS XMM1, XMM0
			; use the Newton-Raphson to refine approximation
			MOVAPS  XMM3, RSQRT_CONST
			MULPS	XMM0, XMM1
			MULPS   XMM0, XMM1
			SUBPS   XMM3, XMM0
			MULPS   XMM3, XMM1
			MOVAPS  XMM1, RSQRT_DIV
			DIVPS   XMM3, XMM1

			;MULPS   XMM0, XMM1

            MULPS   XMM3, XMM2
            MOVUPS  [esi], XMM3
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
		// XMM0 holds the vector
		// XMM1 holds the resulting vector
		// XMM2 holds the broadcast of current working dimension
		// XMM3 holds the transposed column of matrix
        _asm {
			MOV		ecx, vPtr
			MOV     edx, mPtr
			MOV     edi, v
			MOVUPS	XMM0, [ecx]
			; x
			MOVSS	XMM1, XMM0
			SHUFPS  XMM1, XMM1, 00h
			MOVUPS  XMM3, [edx]
			MULPS   XMM1, XMM3
			; y
			MOVAPS  XMM2, XMM0
			SHUFPS  XMM2, XMM2, 55h
			MOVUPS  XMM3, [edx + 16]
			MULPS   XMM2, XMM3
			ADDPS   XMM1, XMM2
			; z
			MOVAPS  XMM2, XMM0
			SHUFPS  XMM2, XMM2, 0AAh
			MOVUPS  XMM3, [edx + 32]
			MULPS   XMM2, XMM3
			ADDPS   XMM1, XMM2
			; w
			MOVAPS  XMM2, XMM0
			SHUFPS  XMM2, XMM2, 0FFh
			MOVUPS  XMM3, [edx + 48]
			MULPS   XMM2, XMM3
			ADDPS   XMM1, XMM2
			; store
			MOVUPS	[edi], XMM1
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

LptaVector LptaVector::operator *(float multiplier) const
{
	return LptaVector(vector.x * multiplier, vector.y * multiplier, vector.z * multiplier);
}

LptaVector LptaVector::operator /(float divisor) const
{
	return LptaVector(vector.x / divisor, vector.y / divisor, vector.z / divisor);
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

// todo: **** Note **** this is in the right-hand rule coordinate system
// while all the matrix stuff is in left-hand rule coordinate system.
// Need to determine whether this is correct or keep everthing consistent.
LptaVector LptaVector::Cross(const LptaVector &other) const
{
	LptaVector result;
	VECTOR &v = result.vector;
	if (sseCapable) {
		const VECTOR *uPtr = &vector;
		const VECTOR *vPtr = &other.vector;
		VECTOR *rPtr = &v;
		_asm {
			
			MOV		esi, uPtr
			MOV		edi, vPtr

			MOVUPS  XMM0, [esi]
			MOVUPS  XMM1, [edi]
			MOVAPS  XMM2, XMM0
			MOVAPS  XMM3, XMM1

			SHUFPS  XMM0, XMM0, 0C9h
			SHUFPS  XMM1, XMM1, 0D2h
			MULPS   XMM0, XMM1

			SHUFPS  XMM2, XMM2, 0D2h
			SHUFPS  XMM3, XMM3, 0C9h
			MULPS   XMM2, XMM3

			SUBPS   XMM0, XMM2

			MOV     edi, rPtr
			MOVUPS	[edi], XMM0
		}
	}
	else {
		v.x = (GetY() * other.GetZ()) - (GetZ() * other.GetY());
		v.y = (GetZ() * other.GetX()) - (GetX() * other.GetZ());
		v.z = (GetX() * other.GetY()) - (GetY() * other.GetX());
	}
	return result;
}