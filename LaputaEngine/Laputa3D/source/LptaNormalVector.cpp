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

}