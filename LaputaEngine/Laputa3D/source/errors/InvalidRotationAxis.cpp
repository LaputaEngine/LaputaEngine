#include "errors/InvalidRotationAxis.h"
#include <string>
using std::to_string;

InvalidRotationAxis::InvalidRotationAxis(const LptaVector &axis) : 
	domain_error(
		"the rotation axis [" + 
			to_string(axis.GetX()) + ", " +
			to_string(axis.GetY()) + ", " +
			to_string(axis.GetZ()) +
		"] is not normal and cannot be used as a rotation axis"
	)
{
}