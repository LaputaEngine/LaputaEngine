#include <Windows.h>
#include <math.h>
#include "LptaVector.h"

bool CheckSSECapability(void);

bool LptaVector::sseCapable = CheckSSECapability();
bool CheckSSECapability(void)
{
	bool hasSSE = false;
	__try {
		_asm {
			MOV		eax, 1
			CPUID
			TEST	edx, 02000000h
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


float LptaVector::GetX(void)
{
	return vector.x;
}

float LptaVector::GetY(void)
{
	return vector.y;
}

float LptaVector::GetZ(void)
{
	return vector.z;
}


float LptaVector::Length(void) const
{
	if (sseCapable) {
		float length;
		float *lengthPtr = &length;
		VECTOR v = vector;
		VECTOR *vPtr = &v;
		_asm {
			MOV		ecx, lengthPtr
			MOV		esi, vPtr
			MOVUPS	XMM0, [esi]
			MULPS	XMM0, XMM0      ; [x*x, y*y, z*z, w*w]
			MOVAPS	XMM1, XMM0
			SHUFPS	XMM1, XMM1, 4Eh ; [z*z, w*w, x*x, y*y]
			ADDPS	XMM0, XMM1      ; [x*x + z*z]
			SHUFPS  XMM1, XMM1, 00h ; [y*y, y*y, y*y, y*y]
			ADDPS	XMM0, XMM1		; [x*x + z*z + y*y]
			SQRTSS	XMM0, XMM0
			MOVSS	[ecx], XMM0
		}
		return length;
	}
	else {
		return sqrt(vector.x * vector.x +
			vector.y + vector.y +
			vector.z + vector.z);
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