#include <string>
#include "resources/errors/TextureD3DFailure.h"

namespace lpta_d3d
{

TextureD3DFailure::TextureD3DFailure(const std::string &reason) : 
    TextureError("encountered error while performing DX9 API calls because: " + reason)
{
}

}