#include "errors/InvalidDimension.h"

InvalidDimension::InvalidDimension(void) :
    runtime_error("attempted to access an invalid dimension")
{
}