#include <string>
#include "resources/errors/TextureError.h"

namespace lpta_d3d
{

TextureError::TextureError(const std::string &reason) : runtime_error(reason)
{
}

}