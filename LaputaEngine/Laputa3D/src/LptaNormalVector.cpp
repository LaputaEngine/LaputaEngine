#include "errors/NonNormalVector.h"
#include "LptaNormalVector.h"

namespace lpta_3d
{

LptaNormalVector::LptaNormalVector(void) : LptaVector()
{
}

LptaNormalVector::LptaNormalVector(float x, float y, float z) : LptaVector(x, y, z)
{
    if (!IsNormal()) {
        throw NonNormalVector(*this);
    }
}

void LptaNormalVector::SetX(float x)
{
    LptaVector::SetX(x);
    // log warning
    Normalize();
}

void LptaNormalVector::SetY(float y)
{
    LptaVector::SetY(y);
    // log warning
    Normalize();
}

void LptaNormalVector::SetZ(float z)
{
    LptaVector::SetZ(z);
    // log warning
    Normalize();
}

}