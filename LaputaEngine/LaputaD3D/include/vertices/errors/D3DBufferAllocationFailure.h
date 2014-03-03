#ifndef _D3DBUFFERALLOCATIONFAILURE_H_
#define _D3DBUFFERALLOCATIONFAILURE_H_

#include <stdexcept>

namespace lpta_d3d
{

class D3DBufferAllocationFailure : public std::runtime_error
{
public:
    D3DBufferAllocationFailure(void);
    ~D3DBufferAllocationFailure(void);
};

}

#endif