#ifndef _LPTAPLANE_H_
#define _LPTAPLANE_H_

#include "LptaNormalVector.h"
#include "geometry/Shapes.h"

namespace lpta_3d
{

class LptaOBB;
class LptaAABB;

class LptaPlane
{
public:
    enum Location
    {
        FRONT,
        BACK,
        PLANE,
    };
public:
    LptaPlane(void);
    LptaPlane(const POINT &point, const LptaNormalVector &normal);
    LptaPlane(const POINT &point, const LptaNormalVector &normal, float distanceToOrigin);
    ~LptaPlane(void);

    inline const POINT &GetPoint(void) const;
    inline const LptaVector &GetNormal(void) const;

    float Distance(const POINT &p) const;
    LptaPlane::Location Classify(const POINT &p) const;
    
    bool Intersects(const LptaPlane &other) const;
    bool Intersects(const LPTA_TRIANGLE &triangle) const;
    bool Intersects(const LptaAABB &aabb) const;
    bool Intersects(const LptaOBB &obb) const;
private:
    POINT point;
    LptaNormalVector normal;
    float distanceToOrigin;
};

const POINT &LptaPlane::GetPoint(void) const
{
    return point;
}

const LptaVector &LptaPlane::GetNormal(void) const
{
    return normal;
}

}

#endif