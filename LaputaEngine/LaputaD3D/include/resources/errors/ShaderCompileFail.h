#ifndef _SHADERCOMPILEFAIL_H_
#define _SHADERCOMPILEFAIL_H_

#include <stdexcept>

namespace lpta_d3d
{
// todo this is too generic, add more error types

class ShaderCompileFail : public std::runtime_error
{
public:
    ShaderCompileFail(void);
    ~ShaderCompileFail(void);
};

}

#endif