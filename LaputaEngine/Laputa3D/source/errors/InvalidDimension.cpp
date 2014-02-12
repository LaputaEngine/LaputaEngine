#include "errors/InvalidDimension.h"

namespace lpta_3d
{

InvalidDimension::InvalidDimension(void) :
    runtime_error("attempted to access an invalid dimension")
{
}

}