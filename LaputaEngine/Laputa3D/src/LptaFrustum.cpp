#include "LptaPlane.h"
#include "LptaFrustum.h"

namespace lpta_3d
{

LptaFrustum::LptaFrustum(void) : LptaFrustum(LptaPlane(), LptaPlane(), 
    LptaPlane(), LptaPlane(), LptaPlane(), LptaPlane())
{
}

LptaFrustum::LptaFrustum(const LptaPlane &left, const LptaPlane &right,
    const LptaPlane &top, const LptaPlane &bottom,
    const LptaPlane &near, const LptaPlane &far)
{
    planes.at(LEFT_FACE) = left;
    planes.at(RIGHT_FACE) = right;
    planes.at(TOP_FACE) = top;
    planes.at(BOTTOM_FACE) = bottom;
    planes.at(NEAR_FACE) = near;
    planes.at(FAR_FACE) = far;
}

LptaFrustum::~LptaFrustum(void)
{
}

const LptaPlane &LptaFrustum::GetPlaneFor(FACE face) const
{
    return planes.at(face);
}

}