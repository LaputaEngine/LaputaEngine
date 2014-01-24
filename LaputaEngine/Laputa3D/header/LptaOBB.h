#ifndef _LPTAOBB_H_
#define _LPTAOBB_H_

#include <array>
#include "LptaNormalVector.h"
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
    LptaOBB(const COORDINATE &coordinate, const OBB_AXES &axes);
    ~LptaOBB(void);

    LptaAABB ConvertToAABB(void) const;
private:
    OBB_AXES axes;
    COORDINATE coordinate;
};

#endif