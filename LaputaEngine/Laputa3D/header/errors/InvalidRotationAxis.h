#ifndef _INVALIDROTATIONAXIS_H_
#define _INVALIDROTATIONAXIS_H_

#include <stdexcept>
#include "LptaVector.h"

class InvalidRotationAxis : public std::domain_error
{
public:
	InvalidRotationAxis(const LptaVector &axis);
};

#endif