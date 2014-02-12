/* Resources used:
 * http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-7-intersecting-simple-shapes/ray-plane-and-ray-disk-intersection/
 */

#include <algorithm>
#include <limits>
#include "Lpta3D.h"
#include "LptaRay.h"

#define INTERSECTS true
#define BARYCENTRIC_LOWER_LIMIT 0.0f
#define BARYCENTRIC_UPPER_LIMIT 1.0f

#define NUM_DIMENSIONS 3

namespace lpta_3d
{

// general
inline bool IsParallel(float denominator);

// Transform(objectMatrix)
inline void Swap(int &a, int &b);

// Intersects(triangle)
inline bool IsOnSamePlane(float determinant);
inline bool IsWithinTriangle(float barycentricCoordinate);

// Intersects(plane)

// Intersects(aabb)

LptaRay::LptaRay(const POINT &origin, const LptaVector &direction) : 
    origin(origin), direction(direction)
{
}

LptaRay::~LptaRay(void)
{
}

LptaRay LptaRay::Transform(LptaMatrix objectMatrix) const
{
    POINT origin = this->origin;
    LptaVector direction = this->direction;

    POINT translation(objectMatrix.GetDx(), objectMatrix.GetDy(), objectMatrix.GetDz());
    origin -= translation;
    objectMatrix.ClearTranslation();
    LptaMatrix inverse = LptaMatrix::MakeInverseFor(objectMatrix);

    origin = origin * inverse;
    direction = origin * inverse;
    return LptaRay(origin, direction);
}

// uses the Moller and Tumbore algorithm
bool LptaRay::Intersects(const LPTA_TRIANGLE &triangle) const
{
    POINT edge1 = triangle.vertices[1] - triangle.vertices[0];
    POINT edge2 = triangle.vertices[2] - triangle.vertices[0];
    LptaVector p = direction.Cross(edge2);
    float determinant = edge1 * p;

    // this tests both sides, the algorithm presented by Moller and Tumbore
    // optionally culls the backface of a triangle.
    if (IsOnSamePlane(determinant)) {
        return !INTERSECTS;
    }

    LptaVector distance = origin - triangle.vertices[0];
    float u = distance * p;
    if (!IsWithinTriangle(u)) {
        return !INTERSECTS;
    }

    LptaVector q = distance.Cross(edge1);
    float v = direction * q;
    if (!IsWithinTriangle(v)) {
        return !INTERSECTS;
    }

    return INTERSECTS;
}
inline bool IsOnSamePlane(float determinant)
{
    return -LPTA_EPSILON < determinant && determinant < LPTA_EPSILON;
}
inline bool IsWithinTriangle(float barycentricCoordinate)
{
    return BARYCENTRIC_LOWER_LIMIT <= barycentricCoordinate &&
        barycentricCoordinate <= BARYCENTRIC_UPPER_LIMIT;
}

bool LptaRay::Intersects(const LptaPlane &plane) const
{
    float denominator = plane.GetNormal() * direction;
    if (IsParallel(denominator)) {
        return !INTERSECTS;
    }
    float intersectDistance = (plane.GetPoint() - origin) * plane.GetNormal();
    intersectDistance /= denominator;
    return intersectDistance >= 0.0f;
}
inline bool IsParallel(float denominator)
{
    return fabs(denominator) < LPTA_EPSILON;
}

// uses the "Fast Ray-Box Intersection" by Andrew Woo
// todo: cleanup... srsly
bool LptaRay::Intersects(const LptaAABB &bBox) const
{
    bool isInside = true;
    POINT intersectCoord;
    LptaVector maxT(-1.0f, -1.0f, -1.0f);
    const POINT &bMin = bBox.GetMin();
    const POINT &bMax = bBox.GetMax();
    // x
    if (origin.GetX() < bMin.GetX()) {
        isInside = false;
        if (direction.GetX() != 0.0f) {
            maxT.SetX((bMin.GetX() - origin.GetX()) / direction.GetX());
        }
    }
    else if (origin.GetX() > bMax.GetX()) {
        isInside = false;
        if (direction.GetX() != 0.0f) {
            maxT.SetX((bMax.GetX() - origin.GetX()) / direction.GetX());
        }
    }
    // y
    if (origin.GetY() < bMin.GetY()) {
        isInside = false;
        if (direction.GetY() != 0.0f) {
            maxT.SetY((bMin.GetY() - origin.GetY()) / direction.GetY());
        }
    }
    else if (origin.GetY() > bMax.GetY()) {
        isInside = false;
        if (direction.GetY() != 0.0f) {
            maxT.SetY((bMax.GetY() - origin.GetY()) / direction.GetY());
        }
    }
    // z
    if (origin.GetZ() < bMin.GetZ()) {
        isInside = false;
        if (direction.GetZ() != 0.0f) {
            maxT.SetZ((bMin.GetZ() - origin.GetZ()) / direction.GetZ());
        }
    }
    else if (origin.GetZ() > bMax.GetZ()) {
        isInside = false;
        if (direction.GetZ() != 0.0f) {
            maxT.SetZ((bMax.GetZ() - origin.GetZ()) / direction.GetZ());
        }
    }

    if (isInside) {
        return INTERSECTS;
    }
    float maxDistance = std::max(maxT.GetX(), maxT.GetY());
    maxDistance = std::max(maxDistance, maxT.GetZ());
    if (maxDistance == -1.0f) {
        return !INTERSECTS;
    }
    // intersects iff all dimensions intersect
    // note that the original implementations saves a branch by saving which plane
    // it uses
    intersectCoord.SetX(origin.GetX() + maxDistance * direction.GetX());
    if (intersectCoord.GetX() < bMin.GetX() - LPTA_EPSILON ||
        bMax.GetX() + LPTA_EPSILON < intersectCoord.GetX()) {
        return !INTERSECTS;
    }
    intersectCoord.SetY(origin.GetY() + maxDistance * direction.GetY());
    if (intersectCoord.GetY() < bMin.GetY() - LPTA_EPSILON ||
        bMax.GetY() + LPTA_EPSILON < intersectCoord.GetY()) {
        return !INTERSECTS;
    }
    intersectCoord.SetZ(origin.GetZ() + maxDistance * direction.GetZ());
    if (intersectCoord.GetZ() < bMin.GetZ() - LPTA_EPSILON ||
        bMax.GetZ() + LPTA_EPSILON < intersectCoord.GetZ()) {
        return !INTERSECTS;
    }
    return INTERSECTS;
}

// uses the slabs algorithm by Moller and Haines
bool LptaRay::Intersects(const LptaOBB &obb) const
{
    using std::numeric_limits;
    float min = -numeric_limits<float>::infinity();
    float max = numeric_limits<float>::infinity();
    POINT p = obb.GetCentre() - origin;
    const OBB_AXES &axes = obb.GetAxes();

    for (OBB_AXES::const_iterator axis = axes.begin(); axis != axes.end(); ++axis) {
        float e = axis->direction * p;
        float f = axis->direction * direction;

        if (!IsParallel(f)) {
            float div = 1 / f;
            float t1 = (e + axis->extent) / 2;
            float t2 = (e - axis->extent) / 2;
            if (t1 > t2) {
                Swap(*(int *)&t1, *(int *)&t2);
            }
            if (t1 > min) {
                min = t1;
            }
            if (t2 < max) {
                max = t2;
            }
            if (min > max) {
                return !INTERSECTS;
            }
            if (max < 0) {
                return !INTERSECTS;
            }
        }
        else if ((-e - axis->extent) > 0 || (-e + axis->extent) < 0) {
            return !INTERSECTS;
        }
    }
    return INTERSECTS;
}
void Swap(int &a, int &b)
{
    a ^= b;
    b = a ^ b;
    a ^= b;
}

}