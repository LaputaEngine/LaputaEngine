#include "LptaPlane.h"
#include "LptaFrustum.h"

namespace lpta_3d
{

LptaFrustum::LptaFrustum(const LptaPlane &left, const LptaPlane &right,
    const LptaPlane &top, const LptaPlane &bottom,
    const LptaPlane &near, const LptaPlane &far)
{
    planes.at(LEFT) = left;
    planes.at(RIGHT) = right;
    planes.at(TOP) = top;
    planes.at(BOTTOM) = bottom;
    planes.at(NEAR) = near;
    planes.at(FAR) = far;
}

LptaFrustum::~LptaFrustum(void)
{
}

const LptaPlane &LptaFrustum::GetPlaneFor(FACE face) const
{
    return planes.at(face);
}

}