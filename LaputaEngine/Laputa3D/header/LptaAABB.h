// LptaAABB (Lpta Axis Aligned Bounding Box)
#ifndef _LPTAAABB_H_
#define _LPTAAABB_H_

#include "LptaVector.h"
#include "LptaBoundingBox.h"

class LptaAABB
{
public:
	LptaAABB(const COORDINATE &min, const COORDINATE &max);
	const LptaBBPlanes GetPlanes(void) const;

	inline const COORDINATE &GetMin(void) const;
	inline const COORDINATE &GetMax(void) const;
	inline const COORDINATE &GetCentre(void) const;
private:
	const COORDINATE min; // near bottom left
	const COORDINATE max; // far top right
	const COORDINATE centre;
};

const COORDINATE &LptaAABB::GetMin(void) const
{
	return min;
}

const COORDINATE &LptaAABB::GetMax(void) const
{
	return max;
}

const COORDINATE &LptaAABB::GetCentre(void) const
{
	return centre;
}

#endif