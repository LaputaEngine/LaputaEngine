#ifndef _D3DCOPIERINVALIDTARGETBUFFER_H_
#define _D3DCOPIERINVALIDTARGETBUFFER_H_

#include <stdexcept>

namespace lpta_d3d
{

class D3DCopierInvalidTargetBuffer : public std::runtime_error
{
public:
    D3DCopierInvalidTargetBuffer(void);
    ~D3DCopierInvalidTargetBuffer(void);
};

}

#endif