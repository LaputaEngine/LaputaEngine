#include "errors/MatrixInversionError.h"

MatrixInversionError::MatrixInversionError(void) :
    runtime_error("matrix is not a suitable candidate for inversion")
{

}