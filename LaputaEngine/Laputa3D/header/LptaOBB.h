#ifndef _LPTAOBB_H_
#define _LPTAOBB_H_

#include <array>
#include "LptaNormalVector.h"
#include "geometry/Shapes.h"
#include "LptaAABB.h"
using std::array;

namespace
{
    static const int NUM_DIM = 3;
}

struct ObbAxis
{
    LptaNormalVector direction;
    float extent;
    LptaVector ExtentVector(void) const
    {
        return direction * extent;
    }
};
typedef array<ObbAxis, NUM_DIM> OBB_AXES;

class LptaOBB
{
public:
    LptaOBB(const COORDINATE &centre, const OBB_AXES &axes);
    ~LptaOBB(void);

    inline const COORDINATE &GetCentre(void) const;
    inline const OBB_AXES &GetAxes(void) const;

    LptaAABB ConvertToAABB(void) const;
    LptaOBB Transform(LptaMatrix transform) const;
private:
    OBB_AXES axes;
    COORDINATE centre;
};

const COORDINATE &LptaOBB::GetCentre(void) const
{
    return centre;
}
const OBB_AXES &LptaOBB::GetAxes(void) const
{
    return axes;
}
#endif