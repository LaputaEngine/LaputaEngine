#include "errors/MatrixInversionError.h"

namespace lpta_3d
{

MatrixInversionError::MatrixInversionError(void) :
    runtime_error("matrix is not a suitable candidate for inversion")
{

}

}