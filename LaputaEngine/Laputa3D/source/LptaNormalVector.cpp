#include "errors/NonNormalVector.h"
#include "LptaNormalVector.h"

LptaNormalVector::LptaNormalVector(void) : LptaVector()
{
}

LptaNormalVector::LptaNormalVector(float x, float y, float z) : LptaVector(x, y, z)
{
	if (!IsNormal()) {
		throw NonNormalVector(*this);
	}
}