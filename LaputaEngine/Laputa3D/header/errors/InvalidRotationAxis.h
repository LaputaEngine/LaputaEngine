#include <stdexcept>
#include "LptaVector.h"

class InvalidRotationAxis : public std::domain_error
{
public:
	InvalidRotationAxis(const LptaVector &axis);
};