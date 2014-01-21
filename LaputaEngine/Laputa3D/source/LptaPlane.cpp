#include "Lpta3D.h"
#include "LptaPlane.h"

// Intersects(plane)
inline bool IsParallel(const LptaVector &crossProduct);

LptaPlane::LptaPlane(void) : LptaPlane(COORDINATE(0.0f, 0.0f, 0.0f), 
	LptaNormalVector::MakeXAlignedVector(LptaVector::POSITIVE))
{
}

LptaPlane::LptaPlane(const COORDINATE &point, const LptaNormalVector &normal)
	: LptaPlane(point, normal, -(normal * point))
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