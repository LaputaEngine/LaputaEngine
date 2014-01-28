#ifndef _LPTAPLANE_H_
#define _LPTAPLANE_H_

#include "LptaNormalVector.h"
#include "geometry/Shapes.h"

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
    LptaPlane(const COORDINATE &point, const LptaNormalVector &normal);
    LptaPlane(const COORDINATE &point, const LptaNormalVector &normal, float distanceToOrigin);
    ~LptaPlane(void);

    inline const COORDINATE &GetPoint(void) const;
    inline const LptaVector &GetNormal(void) const;

    float Distance(const COORDINATE &p) const;
    LptaPlane::Location Classify(const COORDINATE &p) const;
    
    bool Intersects(const LptaPlane &other) const;
    bool Intersects(const LPTA_TRIANGLE &triangle) const;
    bool Intersects(const LptaAABB &aabb) const;
    bool Intersects(const LptaOBB &obb) const;
private:
    COORDINATE point;
    LptaNormalVector normal;
    float distanceToOrigin;
};

const COORDINATE &LptaPlane::GetPoint(void) const
{
    return point;
}

const LptaVector &LptaPlane::GetNormal(void) const
{
    return normal;
}

#endif