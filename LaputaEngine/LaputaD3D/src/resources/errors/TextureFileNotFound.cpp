#include <string>
#include "resources/errors/TextureFileNotFound.h"

namespace lpta_d3d
{

TextureFileNotFound::TextureFileNotFound(const std::string &filename) :
    TextureError("Failed to find texture file " + filename)
{
}

}