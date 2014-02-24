#ifndef _MATRIXINVERSIONERROR_H_
#define _MATRIXINVERSIONERROR_H_
#include <stdexcept>

namespace lpta_3d
{

class MatrixInversionError : public std::runtime_error
{
public:
    MatrixInversionError(void);
};

}

#endif