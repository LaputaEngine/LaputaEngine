#ifndef _NONNORMALVECTOR_H_
#define _NONNORMALVECTOR_H_

#include <stdexcept>
#include "LptaVector.h"

namespace lpta_3d
{

class NonNormalVector : public std::domain_error
{
public:
    NonNormalVector(const LptaVector &vector);
};

}

#endif