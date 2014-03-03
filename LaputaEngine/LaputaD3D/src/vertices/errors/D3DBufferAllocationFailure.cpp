#include "vertices/errors/D3DBufferAllocationFailure.h"

namespace lpta_d3d
{

D3DBufferAllocationFailure::D3DBufferAllocationFailure(void) : 
    runtime_error("failed to allocate buffer")
{
}

D3DBufferAllocationFailure::~D3DBufferAllocationFailure(void)
{
}

}