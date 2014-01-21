/* Resources used:
 */

#include "Lpta3D.h"
#include "LptaAABB.h"
#include "LptaPlane.h"

// Intersects(plane)
inline bool IsParallel(const LptaVector &crossProduct);

LptaPlane::LptaPlane(void) : LptaPlane(COORDINATE(0.0f, 0.0f, 0.0f), 
    LptaNormalVector::MakeXAlignedVector(LptaVector::POSITIVE))
{
}

LptaPlane::LptaPlane(const COORDINATE &point, const LptaNormalVector &normal) : 
    LptaPlane(point, normal, -(normal * point))
{
}

LptaPlane::LptaPlane(const COORDINATE &point, 
    const LptaNormalVector &normal, 
    float distanceToOrigin)
{
    
    this->point = point;
    this->normal = normal;
    this->distanceToOrigin = distanceToOrigin;
}

LptaPlane::~LptaPlane(void)
{
}

float LptaPlane::Distance(const COORDINATE &p) const
{
    return fabs((normal * p) - distanceToOrigin);
}

LptaPlane::Location LptaPlane::Classify(const COORDINATE &p) const
{
    float signedDistance = (p * normal) + distanceToOrigin;
    if (signedDistance < -LPTA_EPSILON) {
        return Location::BACK;
    }
    else if (signedDistance > LPTA_EPSILON) {
        return Location::FRONT;
    }
    else {
        return Location::PLANE;
    }
}

// based on David Eberly's algorithm, with most of the interesting stuff left
// out for now.
bool LptaPlane::Intersects(const LptaPlane &other) const
{
    LptaVector cross = normal.Cross(other.normal);
    
    return !IsParallel(cross);
}
bool IsParallel(const LptaVector &crossProduct)
{
    // note that this is slower than LengthSquared, we me want to optimize
    // this part as the book suggests if needed.
    return crossProduct.Length() < LPTA_EPSILON;
}

bool LptaPlane::Intersects(const LptaAABB &aabb) const
{
    const LptaVector &aabbMin = aabb.GetMin();
    const LptaVector &aabbMax = aabb.GetMax();
    LptaVector min;
    LptaVector max;
    if (normal.GetX() >= 0.0f) {
        min.SetX(aabbMin.GetX());
        max.SetX(aabbMax.GetX());
    }
    else {
        min.SetX(aabbMax.GetX());
        max.SetX(aabbMin.GetX());
    }
    if (normal.GetY() >= 0.0f) {
        min.SetY(aabbMin.GetY());
        max.SetY(aabbMax.GetY());
    }
    else {
        min.SetY(aabbMax.GetY());
        max.SetY(aabbMin.GetY());
    }
    if (normal.GetZ() >= 0.0f) {
        min.SetZ(aabbMin.GetZ());
        max.SetZ(aabbMax.GetZ());
    }
    else {
        min.SetZ(aabbMax.GetZ());
        max.SetZ(aabbMin.GetZ());
    }
    if ((normal * min) + distanceToOrigin > 0.0f) {
        return false;
    }
    if ((normal * max) + distanceToOrigin >= 0.0f) {
        return true;
    }
    return false;
}