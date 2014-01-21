#ifndef _LPTARAY_H_
#define _LPTARAY_H_

#include "LptaVector.h"
#include "LptaPlane.h"
#include "LptaAABB.h"
#include "geometry/Shapes.h"

class LptaRay
{
public:
	LptaRay(const COORDINATE &origin, const LptaVector &direction);
	~LptaRay(void);

	bool Intersects(const LPTA_TRIANGLE &triangle) const;
	bool Intersects(const LptaPlane &plane) const;
	bool Intersects(const LptaAABB &bBox) const;
private:
	const COORDINATE origin;
	const LptaVector direction;
};

#endif