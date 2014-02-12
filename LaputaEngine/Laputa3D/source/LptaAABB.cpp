#include "LptaPlane.h"
#include "LptaNormalVector.h"
#include "LptaAABB.h"

namespace lpta_3d
{

LptaAABB::LptaAABB(const POINT &min, const POINT &max) : 
    min(min), max(max), centre((min + max) / 2)
{
}

const LptaBBPlanes LptaAABB::GetPlanes(void) const
{
    LptaBBPlanes result;
    result[result.FRONT] = 
        LptaPlane(min, LptaNormalVector::MakeZAlignedVector(LptaVector::POSITIVE));
    result[result.BACK] =
        LptaPlane(max, LptaNormalVector::MakeZAlignedVector(LptaVector::NEGATIVE));
    result[result.LEFT] =
        LptaPlane(min, LptaNormalVector::MakeXAlignedVector(LptaVector::NEGATIVE));
    result[result.RIGHT] =
        LptaPlane(max, LptaNormalVector::MakeXAlignedVector(LptaVector::POSITIVE));
    result[result.TOP] =
        LptaPlane(max, LptaNormalVector::MakeYAlignedVector(LptaVector::POSITIVE));
    result[result.BOTTOM] =
        LptaPlane(min, LptaNormalVector::MakeYAlignedVector(LptaVector::NEGATIVE));
    return result;
}

}