#include "Lpta3D.h"
#include "LptaPlane.h"

LptaPlane::LptaPlane(const COORDINATE &point, const LptaNormalVector &normal)
	: LptaPlane(point, normal, -(normal * point))
{
}

LptaPlane::LptaPlane(const COORDINATE &point, const LptaNormalVector &normal, float distanceToOrigin)
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