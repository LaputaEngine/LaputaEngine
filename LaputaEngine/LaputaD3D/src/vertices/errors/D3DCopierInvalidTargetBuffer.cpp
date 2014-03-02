#include "vertices/errors/D3DCopierInvalidTargetBuffer.h"

namespace lpta_d3d
{

D3DCopierInvalidTargetBuffer::D3DCopierInvalidTargetBuffer(void) :
    runtime_error("target buffer is not valid for copy operation")
{
}

D3DCopierInvalidTargetBuffer::~D3DCopierInvalidTargetBuffer(void)
{
}

}