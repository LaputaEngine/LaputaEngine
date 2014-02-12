/* Resources used:
 */

#include "Lpta3D.h"
#include "LptaAABB.h"
#include "LptaOBB.h"
#include "LptaPlane.h"

namespace lpta_3d
{

// Intersects(triangle)
inline bool AllVerticesOnSameSide(const LptaPlane *const plane, const LPTA_TRIANGLE &triangle);

// Intersects(plane)
inline bool IsParallel(const LptaVector &crossProduct);

LptaPlane::LptaPlane(void) : LptaPlane(POINT(0.0f, 0.0f, 0.0f), 
    LptaNormalVector::MakeXAlignedVector(LptaVector::POSITIVE))
{
}

LptaPlane::LptaPlane(const POINT &point, const LptaNormalVector &normal) : 
    LptaPlane(point, normal, -(normal * point))
{
}

LptaPlane::LptaPlane(const POINT &point, 
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

float LptaPlane::Distance(const POINT &p) const
{
    return fabs((normal * p) - distanceToOrigin);
}

LptaPlane::Location LptaPlane::Classify(const POINT &p) const
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

bool LptaPlane::Intersects(const LPTA_TRIANGLE &triangle) const
{
    return !AllVerticesOnSameSide(this, triangle);
}
bool AllVerticesOnSameSide(const LptaPlane *const plane, const LPTA_TRIANGLE &triangle)
{
    return plane->Classify(triangle.vertices[0]) == plane->Classify(triangle.vertices[1]) &&
        plane->Classify(triangle.vertices[1]) == plane->Classify(triangle.vertices[2]);
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

bool LptaPlane::Intersects(const LptaOBB &obb) const
{
    const OBB_AXES &axes = obb.GetAxes();
    float radius = fabs(axes.at(0).extent * (normal * axes.at(1).direction)) +
        fabs(axes.at(1).extent * (normal * axes.at(1).direction)) +
        fabs(axes.at(2).extent * (normal * axes.at(2).direction));
    
    float distance = Distance(obb.GetCentre());
    return distance <= radius;
}

}