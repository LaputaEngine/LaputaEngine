#include "resources/errors/ShaderCompileFail.h"

namespace lpta_d3d
{

ShaderCompileFail::ShaderCompileFail(void) : runtime_error("failed to compile shader")
{
}

ShaderCompileFail::~ShaderCompileFail(void)
{
}

}