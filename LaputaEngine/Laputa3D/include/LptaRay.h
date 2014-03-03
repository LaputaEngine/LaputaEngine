#ifndef _LPTARAY_H_
#define _LPTARAY_H_

#include "LptaVector.h"
#include "LptaPlane.h"
#include "LptaAABB.h"
#include "LptaOBB.h"
#include "geometry/Shapes.h"

namespace lpta_3d
{

class LptaRay
{
public:
    LptaRay(const POINT &origin, const LptaVector &direction);
    ~LptaRay(void);

    LptaRay Transform(LptaMatrix objectMatrix) const;

    bool Intersects(const LPTA_TRIANGLE &triangle) const;
    bool Intersects(const LptaPlane &plane) const;
    bool Intersects(const LptaAABB &bBox) const;
    bool Intersects(const LptaOBB &obb) const;

private:
    const POINT origin;
    const LptaVector direction;
};

}

#endif