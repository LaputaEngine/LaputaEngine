// LptaAABB (Lpta Axis Aligned Bounding Box)
#ifndef _LPTAAABB_H_
#define _LPTAAABB_H_

#include "LptaVector.h"
#include "LptaBoundingBox.h"

namespace lpta_3d
{

class LptaAABB
{
public:
    LptaAABB(const POINT &min, const POINT &max);
    const LptaBBPlanes GetPlanes(void) const;

    inline const POINT &GetMin(void) const;
    inline const POINT &GetMax(void) const;
    inline const POINT &GetCentre(void) const;

private:
    const POINT min; // near bottom left
    const POINT max; // far top right
    const POINT centre;
};

const POINT &LptaAABB::GetMin(void) const
{
    return min;
}

const POINT &LptaAABB::GetMax(void) const
{
    return max;
}

const POINT &LptaAABB::GetCentre(void) const
{
    return centre;
}

}

#endif